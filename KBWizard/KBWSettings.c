#include "KBWSettings.h"
#include <LUFA/Drivers/USB/USB.h>
#include <avr/eeprom.h>
#include <avr/interrupt.h>
#include "InitValues.h"
#include "KBDescr.h"
#include "USBCommand.h"
#include "KBWMouse.h"
#include "KBWKeyboard.h"

#ifdef LEFT_PARK_KEY
#define KEYBOARD_STATUS 0x4C
#else
#define KEYBOARD_STATUS 0x52
#endif
//SendData for USB
unsigned char sendData[HID_GENERIC_EPSIZE]={0x4B,0x42,0x57,KEYBOARD_STATUS,0,0,0,0};
unsigned char mainEEWriteBuffer[200];
unsigned short mainEEAddressBuffer[200];
char requestedValue = 0;
char dataReady = 0;
unsigned char keyMapIndex = 0;

unsigned short currentReadAddress = 0;
unsigned char bytesToReadLeft = 0;
unsigned char currentReadIndex = 0;
unsigned char readedArray[200];
unsigned char EEPROMReadTask = 0;
unsigned char currentKeymapPart = 0;

unsigned char bytesToWriteLeft = 0;
unsigned char currentWriteIndex = 0;
unsigned char waitForWrite = 0;

union {
	uint32_t dword;
	unsigned char arr[4];
} readedDwordUpdate, readedDwordOld;

void initCommon(void) {
	startEERead(0, 3, READ_INITIAL_VALUES);
	initMouse();
	sendData[5] = getSensorId();
	sendData[7] = KBW_VERSION;
}

uint8_t getInitialSensorResolution(void) {
	return eeprom_read_byte(&InitialSensorResolution);
}

void setInitialSensorResolution(uint8_t res) {
	eeprom_write_byte (&InitialSensorResolution, res);
}

uint8_t getInitialSensorWorkType(void) {
	return eeprom_read_byte(&InitialSensorWorkType);
}

void setInitialSensorWorkType(uint8_t type) {
	eeprom_write_byte (&InitialSensorWorkType, type);
}

void ProcessGenericHIDReport(uint8_t* DataArray) {
	if (dataReady) {
		requestedValue = DataArray[0];
		dataReady = 0;
		switch(requestedValue) {
		case KBW_STATUS:
			UpdateStatus();
			break;
		case KBW_SET_SENSOR_RESOLUTION:
			if (startEEWrite(1,1,&DataArray[1])) {
				SetSensorResolution(DataArray[1]);
				UpdateStatus();
			}
			else {
				sendData[0] = 0x42;
				sendData[1] = 0xFF;
				sendData[2] = 0xFF;
				sendData[3] = 0xFF;
				dataReady = 1;
			}
			break;
		case KBW_GET_EEPROM_KB_KEY://4 byte at time
			if ((DataArray[1] < 10)&&(DataArray[2] < 4)&&(DataArray[3]<37)) {
				if (startEERead(128+DataArray[1]*160+DataArray[2]*40+DataArray[3], 4, READ_KEYSET_PART)) {
					sendData[0] = 0x52;
					sendData[1] = DataArray[1];
					sendData[2] = DataArray[2];
					sendData[3] = DataArray[3];
				}
				else {
					sendData[0] = 0x42;
					sendData[1] = 0xFF;
					sendData[2] = 0xFF;
					sendData[3] = 0xFF;
					dataReady = 1;
				}
			}
			else {
				sendData[0] = 0x45;
				dataReady = 1;
			}
			break;
		case KBW_SET_EEPROM_KB_KEY://4 byte at time
			if (waitForWrite) {
				sendData[0] = 0x42;
				sendData[1] = 0xFF;
				sendData[2] = 0xFF;
				sendData[3] = 0xFF;
				dataReady = 1;
			}
			else if ((DataArray[1] < 10)&&(DataArray[2] < 4)&&(DataArray[3]<40)) {
				if (startEEWrite(128+DataArray[1]*160+DataArray[2]*40+DataArray[3], 4,&DataArray[4])) {
					waitForWrite = 1;
					sendData[0] = 0x57;
					sendData[1] = DataArray[1];
					sendData[2] = DataArray[2];
					sendData[3] = DataArray[3];
					sendData[4] = DataArray[4];
					sendData[5] = DataArray[5];
					sendData[6] = DataArray[6];
					sendData[7] = DataArray[7];
				}
				else {
					sendData[0] = 0x42;
					sendData[1] = 0xFF;
					sendData[2] = 0xFF;
					sendData[3] = 0xFF;
					dataReady = 1;
				}
			}
			else {
				sendData[0] = 0x45;
				dataReady = 1;
			}
			break;
		case KBW_SET_KEYMAP:
			if (DataArray[1]<=10) {
				if (startEEWrite(0,1,&DataArray[1])) {
					currentKeymapPart = 0;
					if(startEERead(128 + DataArray[1]*160, 40, READ_KEYSET)) {
						keyMapIndex = DataArray[1];
						UpdateStatus();
					}
					else {
						sendData[0] = 0x42;
						sendData[1] = 0xFF;
						sendData[2] = 0xFF;
						sendData[3] = 0xFF;
						dataReady = 1;
					}
				}
				else {
					sendData[0] = 0x42;
					sendData[1] = 0xFF;
					sendData[2] = 0xFF;
					sendData[3] = 0xFF;
					dataReady = 1;
				}
			}
			break;
		case KBW_UPDATE_KEYMAP:
			currentKeymapPart = 0;
			if(startEERead(128 + keyMapIndex*160, 40, READ_KEYSET)) {
				UpdateStatus();
			}
			else {
				sendData[0] = 0x42;
				sendData[1] = 0xFF;
				sendData[2] = 0xFF;
				sendData[3] = 0xFF;
				dataReady = 1;
			}
			break;
		case KBW_SET_SENSOR_WORK_TYPE:
			if (startEEWrite(2,1,&DataArray[1])) {
				setSensorWorkType(DataArray[1]);
				sendData[0] = 0x54;
				sendData[1] = getSensorWorkType();
				dataReady = 1;
			}
			else {
				sendData[0] = 0x42;
				sendData[1] = 0xFF;
				sendData[2] = 0xFF;
				sendData[3] = 0xFF;
				dataReady = 1;
			}
			break;
		case KBW_GET_SENSOR_WORK_TYPE:
			sendData[0] = 0x54;
			sendData[1] = getSensorWorkType();
			dataReady = 1;
			break;
		case KBW_GET_KEY_PRESS_STATISTIC:
			if (DataArray[1] < 40) {
				if(startEERead(128 + 1600 + DataArray[1]*4, 4, READ_KEYSET_STATISTIC)) {
					sendData[0] = 0x53;
					sendData[1] = DataArray[1];
					sendData[2] = 0;
					sendData[3] = 0;
				}
				else {
					sendData[0] = 0x42;
					sendData[1] = 0xFF;
					sendData[2] = 0xFF;
					sendData[3] = 0xFF;
					dataReady = 1;
				}
			}
			else {
				sendData[0] = 0x45;
			}
			dataReady = 1;
			break;
		case KBW_UPDATE_EEPROM_KEY:
			if (waitForWrite) {
				sendData[0] = 0x42;
				sendData[1] = 0xFF;
				sendData[2] = 0xFF;
				sendData[3] = 0xFF;
				dataReady = 1;
			}
			else if ((DataArray[1] < 10)&&(DataArray[2] < 4)&&(DataArray[3]<40)) {
				if (startEEWrite(128+DataArray[1]*160+DataArray[2]*40+DataArray[3], 1,&DataArray[4])) {
					waitForWrite = 1;
					startEEWrite(128+DataArray[1]*160+DataArray[2]*40+40+DataArray[3], 1,&DataArray[5]);
					sendData[0] = 0x57;
					sendData[1] = DataArray[1];
					sendData[2] = DataArray[2];
					sendData[3] = DataArray[3];
					sendData[4] = DataArray[4];
					sendData[5] = DataArray[5];
					sendData[6] = 0;
					sendData[7] = 0;
					if (DataArray[1] == keyMapIndex) {
						if (DataArray[2] == 0) updateNmKey(DataArray[4], DataArray[5], DataArray[3]);
						else updateFnKey(DataArray[4], DataArray[5], DataArray[3]);
					}
				}
				else {
					sendData[0] = 0x42;
					sendData[1] = 0xFF;
					sendData[2] = 0xFF;
					sendData[3] = 0xFF;
					dataReady = 1;
				}
			}
			else {
				sendData[0] = 0x45;
				dataReady = 1;
			}
			break;
		case KBW_GET_CURRENT_KEY_STATE:
			getKBStatus(sendData);
			dataReady = 1;
			break;

		case KBW_READ_RESERVED:
			eeprom_read_block(&sendData[3], &(ReservedEEMEM[DataArray[1]]), 1);
			sendData[4] = readEEKBKey(DataArray[2], DataArray[3], DataArray[4]);
			//uint32_t v = ReadKPStatEEMEM(DataArray[1]);
			sendData[0] = 0x51;
			sendData[1] = DataArray[1];
			sendData[2] = DataArray[2];
			//sendData[3] = v & 0xFF;
			dataReady = 1;
			break;
		default: break;
		}
	}
}
void CreateGenericHIDReport(uint8_t* DataArray) {
	if (dataReady) {
		for (int i = 0; i < HID_GENERIC_EPSIZE; i++) {
			DataArray[i] = sendData[i];
		}
	}
	else {
		DataArray[0] = 0xFF;
		DataArray[1] = 0xFF;
		DataArray[2] = 0xFF;
		DataArray[3] = 0xFF;
	}
}

void HID_Task(void) {
	if (USB_DeviceState != DEVICE_STATE_Configured) return; //Device must be connected and configured for the task to run
	uint8_t GenericData[HID_EPSIZE]; //Create a temporary buffer to hold the report to send to the host
	Endpoint_SelectEndpoint(GENERIC_IN_EPADDR);
	if (Endpoint_IsINReady()) { //Check to see if the host is ready to accept another packet
		CreateGenericHIDReport(GenericData); //Create Generic Report Data
		Endpoint_Write_Stream_LE(&GenericData, sizeof(GenericData), NULL); //Write Generic Report Data
		Endpoint_ClearIN(); //Finalize the stream transfer to send the last packet
	}
	Endpoint_SelectEndpoint(GENERIC_OUT_EPADDR);
	if (Endpoint_IsOUTReceived()) { //Check to see if a packet has been sent from the host
		if (Endpoint_IsReadWriteAllowed()) { //Check to see if the packet contains data
			Endpoint_Read_Stream_LE(&GenericData, sizeof(GenericData), NULL); //Read Generic Report Data
			ProcessGenericHIDReport(GenericData);//Process Generic Report Data
			Endpoint_ClearOUT();
		}
	}
}


void UpdateStatus(void) {
	sendData[0] = 0x4B;//K
	sendData[1] = 0x42;//B
	sendData[2] = 0x57;//W
	sendData[3] = KEYBOARD_STATUS;//R\L
	sendData[4] = keyMapIndex;
	sendData[5] = getSensorId();
	sendData[6] = getSensorRes();
	sendData[7] = KBW_VERSION;
	dataReady = 1;
}

char startEERead(unsigned short address, unsigned char count, unsigned char task) {
	if ((bytesToReadLeft == 0)&&(count <= 200)) {
		currentReadIndex = 0;
		currentReadAddress = address;
		bytesToReadLeft = count;
		EEPROMReadTask = task;
		return 1;
	}
	return 0;
}

unsigned short getCurrentReadAddress (void) {
	return currentReadAddress;
}

unsigned char getBytesReadLeft (void) {
	return bytesToReadLeft;
}

unsigned char *getReadArray (void) {
	return readedArray;
}

unsigned char readEEByte (unsigned short address) {
	cli();
	EEAR = address;
	EECR |= _BV(EERE);
	char a = EEDR;
	sei();
	return a;
}

void writeEEByte (unsigned short address, unsigned char value) {
	cli();
	EEAR = address;
	EEDR = value;
	EECR |= _BV(EEMPE);
	EECR |= _BV(EEPE);
	sei();
}

void readEEPROMData (void) {
	if (bytesToReadLeft > 0) {
		if (!(EECR & _BV(EEPE))) {
			readedArray[currentReadIndex] = readEEByte (currentReadAddress);
			currentReadAddress++;
			bytesToReadLeft--;
			currentReadIndex++;
		}
	}
	else if (EEPROMReadTask) {
		switch (EEPROMReadTask) {
		case READ_INITIAL_VALUES:
			EEPROMReadTask = 0;
			keyMapIndex = readedArray[0];
			if (keyMapIndex > 9) keyMapIndex = 9;
			SetSensorResolution(readedArray[1]);
			setSensorWorkType(readedArray[2]);
			sendData[4] = keyMapIndex;
			sendData[6] = getSensorRes();
			dataReady = 1;
			if (currentKeymapPart < 4) {
				startEERead(128 + keyMapIndex*160+currentKeymapPart*40, 40, READ_KEYSET);
			}
			break;
		case READ_KEYSET:
			EEPROMReadTask = 0;
			updateKeymap(readedArray, currentKeymapPart);
			currentKeymapPart++;
			if (currentKeymapPart < 4) {
				startEERead(currentReadAddress, 40, READ_KEYSET);
			}
			else {
				startEERead(128 + 1600, 160, READ_KEYSET_STAT_INIT);
			}
			break;
		case READ_KEYSET_PART:
			EEPROMReadTask = 0;
			sendData[4] = readedArray[0];
			sendData[5] = readedArray[1];
			sendData[6] = readedArray[2];
			sendData[7] = readedArray[3];
			dataReady = 1;
			break;
		case READ_KEYSET_STATISTIC:
			EEPROMReadTask = 0;
			sendData[4] = readedArray[0];
			sendData[5] = readedArray[1];
			sendData[6] = readedArray[2];
			sendData[7] = readedArray[3];
			dataReady = 1;
			break;
		case READ_KEYSET_STAT_INIT:
			EEPROMReadTask = 0;
			updateKeystat((uint32_t*)readedArray);
			break;
		default: break;
		}
	}
}

char startEEWrite(unsigned short address, unsigned char count, unsigned char *toWrite) {
	if (bytesToWriteLeft + count < 100) {
		if (bytesToWriteLeft == 0) currentWriteIndex = 0;
		for (int i = currentWriteIndex + bytesToWriteLeft, j = 0; j < count; i++, j++) {
			mainEEWriteBuffer[i] = toWrite[j];
			mainEEAddressBuffer[i] = address + j;
		}
		bytesToWriteLeft += count;
		return 1;
	}
	return 0;
}

void writeEEPROMData (void) {
	if (bytesToWriteLeft > 0) {
		if (!(EECR & _BV(EEPE))) {
			writeEEByte (mainEEAddressBuffer[currentWriteIndex], mainEEWriteBuffer[currentWriteIndex]);
			bytesToWriteLeft--;
			currentWriteIndex++;
		}
	}
	else if (!dataReady&&waitForWrite) {
		waitForWrite = 0;
		dataReady = 1;
	}
}
