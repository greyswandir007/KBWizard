#include "KBWizard.h"

#define FNOUTPORT PORTB
#define FNPORTPIN PINB
#define FNOUTPIN 5
#define FNINPIN 0
#define MOUSEOUTPIN 2
#define MOUSEINPIN 3
#define MOUSESSPIN 4
#define MOUSERESPIN 5
int main(void) {
	SetupHardware();
	GlobalInterruptEnable();
	initCommon();
	for (;;) {
		scanKeyPressed();
		MouseReadSensor();
		Keyboard_HID_Task();
		Consumer_HID_Task();
		Mouse_HID_Task();
		HID_Task();
		USB_USBTask();
		readEEPROMData ();
		writeEEPROMData ();
	}
}
void SetupHardware(void) {//Configures the board hardware and chip peripherals for the demo's functionality.
#if (ARCH == ARCH_AVR8)
	MCUSR &= ~(1 << WDRF);//Disable watchdog if enabled by bootloader/fuses
	wdt_disable();
	clock_prescale_set(clock_div_1);//Disable clock division
#elif (ARCH == ARCH_XMEGA)
	XMEGACLK_StartPLL(CLOCK_SRC_INT_RC2MHZ, 2000000, F_CPU);/* Start the PLL to multiply the 2MHz RC oscillator to 32MHz and switch the CPU core to run from it */
	XMEGACLK_SetCPUClockSource(CLOCK_SRC_PLL);
	XMEGACLK_StartInternalOscillator(CLOCK_SRC_INT_RC32MHZ); /* Start the 32MHz internal RC oscillator and start the DFLL to increase it to 48MHz using the USB SOF as a reference */
	XMEGACLK_StartDFLL(CLOCK_SRC_INT_RC32MHZ, DFLL_REF_INT_USBSOF, F_USB);
	PMIC.CTRL = PMIC_LOLVLEN_bm | PMIC_MEDLVLEN_bm | PMIC_HILVLEN_bm;
#endif
	//Configure key ports
	DDRA = 0; PORTA = 0xFF;
	DDRC = 0; PORTC = 0xFF;
	DDRD = 0; PORTD = 0xFF;
	DDRE = 0; PORTE = 0xFF;
	DDRF = 0; PORTF = 0xFF;

	DDRB = 0b00000111 | _BV(FNOUTPIN); PORTB = 0xFF;
	USB_Init();
}
void EVENT_USB_Device_Connect(void) { //On connect
}
void EVENT_USB_Device_Disconnect(void) { //On disconnect
}
void EVENT_USB_Device_ConfigurationChanged(void) {
	bool ConfigSuccess = true;
	/* Setup Keyboard HID Report Endpoints */
	ConfigSuccess &= Endpoint_ConfigureEndpoint(KEYBOARD_IN_EPADDR, EP_TYPE_INTERRUPT, HID_EPSIZE, 1);
	ConfigSuccess &= Endpoint_ConfigureEndpoint(KEYBOARD_OUT_EPADDR, EP_TYPE_INTERRUPT, HID_EPSIZE, 1);
	/* Setup Mouse HID Report Endpoint */
	ConfigSuccess &= Endpoint_ConfigureEndpoint(MOUSE_IN_EPADDR, EP_TYPE_INTERRUPT, HID_EPSIZE, 1);
	/* Setup Consumer HID Report Endpoint */
	ConfigSuccess &= Endpoint_ConfigureEndpoint(CONSUMER_IN_EPADDR, EP_TYPE_INTERRUPT, HID_EPSIZE, 1);
	/* Setup Generic HID Report Endpoint */
	ConfigSuccess &= Endpoint_ConfigureEndpoint(GENERIC_IN_EPADDR, EP_TYPE_INTERRUPT, HID_EPSIZE, 1);
	ConfigSuccess &= Endpoint_ConfigureEndpoint(GENERIC_OUT_EPADDR, EP_TYPE_INTERRUPT, HID_EPSIZE, 1);
	//LEDs_SetAllLEDs(ConfigSuccess ? LEDMASK_USB_READY : LEDMASK_USB_ERROR);/* Indicate endpoint configuration success or failure */
}
/** Event handler for the USB_ControlRequest event. This is used to catch and process control requests sent to
 *  the device from the USB host before passing along unhandled control requests to the library for processing
 *  internally. */
void EVENT_USB_Device_ControlRequest(void) {
	uint8_t* ReportData;
	uint8_t  ReportSize;
	/* Handle HID Class specific requests */
	switch (USB_ControlRequest.bRequest) {
		case HID_REQ_GetReport:
			if (USB_ControlRequest.bmRequestType == (REQDIR_DEVICETOHOST | REQTYPE_CLASS | REQREC_INTERFACE)) {
				Endpoint_ClearSETUP();
				/* Determine if it is the mouse or the keyboard data that is being requested */
				if (USB_ControlRequest.wIndex == INTERFACE_ID_Keyboard) {
					ReportData = getKBReportData();
					ReportSize = getKBReportSize();
				}
				else if (USB_ControlRequest.wIndex == INTERFACE_ID_Mouse) {
					ReportData = getMSReportData();
					ReportSize = getMSReportSize();
				}
				else if (USB_ControlRequest.wIndex == INTERFACE_ID_Consumer) {
					ReportData = getConsReportData();
					ReportSize = getConsReportSize();
				}
				else {
					uint8_t GenericData[HID_GENERIC_EPSIZE];
					CreateGenericHIDReport(GenericData);
					ReportData = GenericData;
					ReportSize = sizeof(GenericData);
				}
				/* Write the report data to the control endpoint */
				Endpoint_Write_Control_Stream_LE(ReportData, ReportSize);
				Endpoint_ClearOUT();
				/* Clear the report data afterwards */
				memset(ReportData, 0, ReportSize);
			}
			break;
		case HID_REQ_SetReport:
			if (USB_ControlRequest.bmRequestType == (REQDIR_HOSTTODEVICE | REQTYPE_CLASS | REQREC_INTERFACE)) {
				Endpoint_ClearSETUP();
				/* Wait until the LED report has been sent by the host */
				while (!(Endpoint_IsOUTReceived())) {
					if (USB_DeviceState == DEVICE_STATE_Unattached)
					  return;
				}
				/* Read in the LED report from the host */
				uint8_t GenericData[HID_GENERIC_EPSIZE];
				uint8_t LEDStatus = 0;
				if (USB_ControlRequest.wIndex == INTERFACE_ID_Keyboard) {
					LEDStatus = Endpoint_Read_8();
				}
				else if (USB_ControlRequest.wIndex == INTERFACE_ID_Generic) {
					Endpoint_Read_Control_Stream_LE(&GenericData, sizeof(GenericData));
				}
				Endpoint_ClearIN();
				Endpoint_ClearStatusStage();
				/* Process the incoming LED report */
				if (USB_ControlRequest.wIndex == INTERFACE_ID_Keyboard) {
					Keyboard_ProcessLEDReport(LEDStatus);
				}
				else if (USB_ControlRequest.wIndex == INTERFACE_ID_Generic) {
					ProcessGenericHIDReport(GenericData);
				}
			}
			break;
	}
}
