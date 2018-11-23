#include "KBWMouse.h"
#include <LUFA/Drivers/USB/USB.h>
#include "KBDescr.h"
#include "USBCommand.h"
#include "KBWSettings.h"
#include "KBWKeyboard.h"
#define MOUSESSPIN 4
typedef struct{
	uint8_t Button; /**< Button mask for currently pressed buttons in the mouse. */
	int8_t  X; /**< Current delta X movement of the mouse. */
	int8_t  Y; /**< Current delta Y movement on the mouse. */
	int8_t  wheelY; /**< Current delta X wheel movement of the mouse. */
	int8_t  wheelX; /**< Current delta Y wheel movement on the mouse. */
}ATTR_PACKED USB_MouseReport_Data_Wheel_t;
static USB_MouseReport_Data_Wheel_t MouseReportData; /** Global structure to hold the current mouse interface HID report, for transmission to the host */
char sensorAttached = 0;
//Mouse Global variables
char sensorResolution = 8;
short mouseOffsetX = 0;
short mouseOffsetY = 0;
volatile char preva = 0;
unsigned char mouseDeviceId = 0;
unsigned char sensorWorkType = 0;

void initMouse(void) {
	SPCR = 0b01011101; //7 - Interrupt disabled,  6 - SPI ON, 5 - MSB, 4 - Master, 3 - Clock polarity 1, 2 - Falling, 0-1 - 1Mhz (f/16)
	//char resolution = getInitialSensorResolution();
	//sensorWorkType = getInitialSensorWorkType();
	//if (resolution == 0) resolution = 8;
	char dev = ReadSensorValue(0x00);
	char rev = ReadSensorValue(0x01);
	mouseDeviceId = dev;
	if (dev == 0x12) {
		if ((rev>=0x01)&&(rev <= 0x08)) {
			sensorAttached = 1;
			//SetSensorResolution(resolution);
		}
	}
	memset(&MouseReportData, 0, sizeof(MouseReportData)); //Clear the report data
}

uint8_t getModifierForMouse(void){

	uint8_t mod = 0;
	if ((mouseOffsetX != 0)||(mouseOffsetY != 0)) mod = sensorWorkType >> 4;
	return mod;
}

uint8_t getSensorId(void) {
	return mouseDeviceId;
}

uint8_t getSensorRes(void) {
	return sensorResolution;
}

uint8_t getSensorWorkType(void) {
	return sensorWorkType;
}
void setSensorWorkType(uint8_t type) {
	sensorWorkType = type;
}

uint8_t* getMSReportData(void) {
	return (uint8_t*)&MouseReportData;
}
uint8_t  getMSReportSize(void) {
	return sizeof(MouseReportData);
}

void Mouse_HID_Task(void) { //Generates the next mouse HID report for the host
	if (USB_DeviceState != DEVICE_STATE_Configured) return; /* Device must be connected and configured for the task to run */
	MouseReportData.Button = getMouseBtnState() | ((sensorWorkType&0x0F)>>1);
	if (sensorWorkType&0x01) {
		MouseReportData.wheelX = mouseOffsetX;
		MouseReportData.wheelY = mouseOffsetY;
	}
	else {
		MouseReportData.X = mouseOffsetX;
		MouseReportData.Y = mouseOffsetY;
	}
	Endpoint_SelectEndpoint(MOUSE_IN_EPADDR); //Select the Mouse Report Endpoint
	if (Endpoint_IsReadWriteAllowed()) { //Check if Mouse Endpoint Ready for Read/Write
		Endpoint_Write_Stream_LE(&MouseReportData, sizeof(MouseReportData), NULL); //Write Mouse Report Data
		Endpoint_ClearIN(); //Finalize the stream transfer to send the last packet
		memset(&MouseReportData, 0, sizeof(MouseReportData)); //Clear the report data afterwards
		mouseOffsetX = 0;
		mouseOffsetY = 0;
	}
}

void MouseReadSensor(void) {
	if (sensorAttached) {
		unsigned char motion = ReadSensorValue(0x02);
		if(motion & 0x80) {
			mouseOffsetX +=(short)ReadSensorValue(0x03);
			_delay_us(1);
			mouseOffsetY += (short)ReadSensorValue(0x04);
		}
	}
}

void WriteSPIByte(char adr) {
	volatile char a = 0;
	a = preva;
	SPDR = adr;
	while(!(SPSR & _BV(SPIF))) a++;
	preva = a;
}

char ReadSPIByte(void) {
	volatile char a = 0;
	a = preva;
	SPDR = 0;
	while(!(SPSR & _BV(SPIF))) a++;
	preva = a;
	char b = SPDR;
	return b;
}

char ReadSensorValue(char adr) {
	PORTB &= ~_BV(MOUSESSPIN);
	WriteSPIByte(adr);
	_delay_us(7);
	char res = ReadSPIByte();
	PORTB |= _BV(MOUSESSPIN);
	return res;
}

void WriteSensorValue(char adr, char value) {
	PORTB &= ~_BV(MOUSESSPIN);
	WriteSPIByte(adr);
	_delay_us(7);
	WriteSPIByte(value);
	PORTB |= _BV(MOUSESSPIN);
}

void SetSensorResolution (unsigned char res) {
	if ((res >= 1)&&(res <= 11)&&(sensorResolution != res)) {
		res = res & 0x0F;
		sensorResolution = res;
		res = res | 0x10;
		WriteSensorValue(0x19, res);
		setInitialSensorResolution(sensorResolution);
	}
}

