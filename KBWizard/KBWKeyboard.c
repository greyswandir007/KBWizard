#include "KBWKeyboard.h"
#include <LUFA/Drivers/USB/USB.h>
#include <avr/eeprom.h>
#include "KBDescr.h"
#include "USBCommand.h"
#include "KBWMouse.h"
#include "KBWSettings.h"
#ifdef LEFT_PART_KEY
#include "keymapLeft.h"
#define KEYBOARD_STATUS 0x4C
#else
#include "keymapRight.h"
#define KEYBOARD_STATUS 0x52
#endif
#define FNOUTPORT PORTB
#define FNPORTPIN PINB
#define FNOUTPIN 6
#define FNINPIN 7
typedef struct{
	uint8_t ReportID; /**< Button mask for currently pressed buttons in the mouse. */
	int8_t  Buttons1; /**< Current delta X movement of the mouse. */
	int8_t  Buttons2; /**< Current delta Y movement on the mouse. */
} ATTR_PACKED USB_ConsumerReport_Data;
static USB_KeyboardReport_Data_t KeyboardReportData; /** Global structure to hold the current keyboard interface HID report, for transmission to the host */
static USB_ConsumerReport_Data ConsumerReportData;
//Keyboard Global variables
uint8_t kmMain[KEYMAP_SIZE]; // keyMap
uint8_t kmMMod[KEYMAP_SIZE]; // keyMapMod
uint8_t kmFn[KEYMAP_SIZE];   // keyMapFn
uint8_t kmFMod[KEYMAP_SIZE]; // keyMapFnMod
uint8_t kpStatPress[KEYMAP_SIZE] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
uint8_t kpStatImidiate[KEYMAP_SIZE] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
uint32_t kpStat[KEYMAP_SIZE];

uint8_t keyPressed[20];
uint8_t countKeyPressed = 0;
uint8_t keyPressModifier;
uint8_t mouseButton = 0;
uint8_t fnPressed = 0;
uint8_t consumerButton[3] = {0, 0, 0};

uint8_t hasFn = 0;
uint8_t isBlocked = 0;
uint8_t isBlockKeyPressed = 0;
uint8_t fnPort[8] = {0,0,0,0,0,0,0,0}; // 0 - PORTA, 1 - PORTC, 2 - PORTD, 3 - PORTE, 4 - PORTF,
			  // PORTF&0x80 - external fn
			  // PORTF&0x40 - should set for external fn
uint8_t fnPin[8] = {0,0,0,0,0,0,0,0};
uint8_t pressedButtons[5] = {0,0,0,0,0};
uint16_t emptyCycles = 0;    //0xE8  0xE9  0xEA  0xEB  0xEC  0xED  0xEE  0xEF  0xF0  0xF1  0xF2  0xF3  0xF4  0xF5  0xF6  0xF7  0xF8  0xF9  0xFA  0xFB  0xFC  0xFD
uint8_t consumer_SC_Codes[] = {0x08, 0x10, 0x20, 0x40, 0x80, 0x02, 0x04, 0x01, 0x04, 0x80, 0x40, 0x20, 0x02, 0x00, 0x00, 0x00, 0x01, 0x00, 0x10, 0x01, 0x08, 0x02};
uint8_t consumer_SC_Btn[]   = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x01, 0x01, 0x01, 0x01, 0x00, 0x00, 0x00, 0x02, 0x00, 0x01, 0x01, 0x01, 0x02};

void fillPortKey(uint8_t *btn, uint8_t *map, uint8_t *mod) {
	uint8_t blockKeyPressed = 0;
	if (btn && countKeyPressed < 20) {
		int j = 0;
		for(int k = 0; k < 5; k++) {
			for (int i = 0; i < 8; i++) {
				if (btn[k] & _BV(i)) {
					if (map[j] >= 0xF5 && map[j] <= 0xF7) mouseButton |= 1 << (map[j] - 0xF5);
					if (map[j] >= 0xE0 && map[j] <= 0xE7) keyPressModifier |= 1 << (map[j] - 0xE0);
					if (map[j] >= 0xE8 && map[j] <= 0xFD) {
						uint8_t cc = map[j]-0xE8;
						consumerButton[consumer_SC_Btn[cc]] |= consumer_SC_Codes[cc];
						//01//Vol mute;			HID_KEYBOARD_SC_MEDIA_MUTE                        0xEF
						//02//Vol Up			HID_KEYBOARD_SC_MEDIA_VOLUME_UP                   0xED
						//04//Vol down			HID_KEYBOARD_SC_MEDIA_VOLUME_DOWN                 0xEE
						//08//Play/Pause		HID_KEYBOARD_SC_MEDIA_PLAY                        0xE8
						//10//Stop				HID_KEYBOARD_SC_MEDIA_STOP                        0xE9
						//20//Prev Track		HID_KEYBOARD_SC_MEDIA_PREVIOUS_TRACK              0xEA
						//40//Next Track		HID_KEYBOARD_SC_MEDIA_NEXT_TRACK                  0xEB
						//80//Mail				HID_KEYBOARD_SC_MEDIA_EJECT                       0xEC

						//01//Calculator		HID_KEYBOARD_SC_MEDIA_CALCULATOR                  0xFB
						//02//Search			HID_KEYBOARD_SC_MEDIA_SEARCH                      0xF4
						//04//Home				HID_KEYBOARD_SC_MEDIA_WWW                         0xF0
						//08//Favorites			0xFC
						//10//Refresh			HID_KEYBOARD_SC_MEDIA_RELOAD                      0xFA
						//20//www stop			HID_KEYBOARD_SC_MEDIA_CANCEL                      0xF3
						//40//www forward		HID_KEYBOARD_SC_MEDIA_FORWARD                     0xF2
						//80//www back			HID_KEYBOARD_SC_MEDIA_BACKWARD                    0xF1

						//01//Sleep				HID_KEYBOARD_SC_MEDIA_SLEEP                       0xF8
						//02//Wake				0xFD
					}
					if (map[j] && countKeyPressed < 20 && map[j] < 0xE8) {
						keyPressed[countKeyPressed] = map[j];
						keyPressModifier |= mod[j];
						countKeyPressed++;
					}
					if (map[j] == NONHID_BLOCK_KEYBOARD) {
						blockKeyPressed = 1;
						isBlockKeyPressed = 1;
					}
					kpStatPress[j] = 1;
				} else if (kpStatPress[j]) {
					kpStatPress[j] = 0;
					kpStatImidiate[j]++;
					kpStat[j]++;
				}
				if (kpStatImidiate[j] >= 10) {
					if (startEEWrite(128 + 1600 + j * 4, 4, (uint8_t*)&(kpStat[j]))) kpStatImidiate[j] = 0;
				}
				if (emptyCycles >= 8000 && kpStatImidiate[j] > 0) {
					if (startEEWrite(128 + 1600 + j * 4, 4, (uint8_t*)&(kpStat[j]))) kpStatImidiate[j] = 0;
				}
				j++;
			}
		}
	}
	if (isBlockKeyPressed && !blockKeyPressed) {
		isBlocked ^= 1;
	}
}

uint8_t* getKBReportData(void) {
	return (uint8_t*)&KeyboardReportData;
}
uint8_t  getKBReportSize(void) {
	return sizeof(KeyboardReportData);
}
uint8_t* getConsReportData(void) {
	return (uint8_t*)&ConsumerReportData;
}
uint8_t  getConsReportSize(void) {
	return sizeof(ConsumerReportData);
}
uint8_t getMouseBtnState(void) {
    return mouseButton;
}
void getKBStatus(uint8_t* dataArray) {
	if (fnPressed) dataArray[0] = 0x50;//P //p
	else dataArray[0] = 0x70;//p
    dataArray[1] = pressedButtons[0];
    dataArray[2] = pressedButtons[1];
    dataArray[3] = pressedButtons[2];
    dataArray[4] = pressedButtons[3];
    dataArray[5] = pressedButtons[4];
    dataArray[6] = consumerButton[0];
    dataArray[7] = consumerButton[1];
}

void scanKeyPressed() {
    mouseButton = 0;
	fnPressed = 0;
	countKeyPressed = 0;
	keyPressModifier = 0;
	consumerButton[0] = 0;
	consumerButton[1] = 0;
	consumerButton[2] = 0;
	uint8_t btn[5];
	btn[0] = PINA; btn[1] = PINC; btn[2] = PINE; btn[3] = PINF;
	btn[4] = PIND;
	btn[4] = btn[4] & 0x13 | ((btn[4] & 0xC0) >> 4) | (PINB & 0xF0);
	for (int i = 0; i < 5; i++) {
		btn [i] = ~btn[i];
		pressedButtons [i] = btn[i];
	}
	for(int i = 0; i < hasFn; i++) {
        if (fnPort[i] >= 0 && fnPort[i] <= 5 && (btn[fnPort[i]] & _BV(fnPin[i]) == 0)) {
            fnPressed = 1;
        }
    }
	unsigned char *map = kmMain, *mod = kmMMod;
	if (fnPressed) {map = kmFn; mod = kmFMod;}
	fillPortKey (btn, map, mod);

	if (countKeyPressed == 0) emptyCycles++;
	else emptyCycles = 0;
	if (emptyCycles>= 10000) emptyCycles = 0;
}

void Keyboard_ProcessLEDReport(const uint8_t LEDStatus) {// Processes a given Keyboard LED report from the host, and sets the board LEDs to match.
}

void Keyboard_HID_Task(void) {//Generates the next keyboard HID report for the host. Processes host LED status.
	if (USB_DeviceState != DEVICE_STATE_Configured) return;//Device must be connected and configured for the task to run

	if (!isBlocked) {
		KeyboardReportData.Modifier = keyPressModifier | getModifierForMouse();
		for (int i = 0; (i < 6) && (i < countKeyPressed); i++) KeyboardReportData.KeyCode[i] = keyPressed[i];
	}

	Endpoint_SelectEndpoint(KEYBOARD_IN_EPADDR); //Select the Keyboard Report Endpoint
	if (Endpoint_IsReadWriteAllowed()) {//Check if Keyboard Endpoint Ready for Read/Write
		Endpoint_Write_Stream_LE(&KeyboardReportData, sizeof(KeyboardReportData), NULL); //Write Keyboard Report Data
		Endpoint_ClearIN(); //Finalize the stream transfer to send the last packet
		memset(&KeyboardReportData, 0, sizeof(KeyboardReportData)); //Clear the report data afterwards
	}
	Endpoint_SelectEndpoint(KEYBOARD_OUT_EPADDR); //Select the Keyboard LED Report Endpoint
	if (Endpoint_IsReadWriteAllowed()) { //Check if Keyboard LED Endpoint Ready for Read/Write
		Keyboard_ProcessLEDReport(Endpoint_Read_8()); //Read in and process the LED report from the host
		Endpoint_ClearOUT(); //Handshake the OUT Endpoint - clear endpoint and ready for next report */
	}
}

void Consumer_HID_Task(void) {
    if (!isBlocked) {
		if (consumerButton[2] != 0) {
			ConsumerReportData.ReportID = 2;
			ConsumerReportData.Buttons1 = consumerButton[2];
			ConsumerReportData.Buttons2 = 0;
		} else {
			ConsumerReportData.ReportID = 1;
			ConsumerReportData.Buttons1 = consumerButton[0];
			ConsumerReportData.Buttons2 = consumerButton[1];
		}
	}
	Endpoint_SelectEndpoint(CONSUMER_IN_EPADDR); //Select the Keyboard Report Endpoint
	if (Endpoint_IsReadWriteAllowed()) {//Check if Keyboard Endpoint Ready for Read/Write
		Endpoint_Write_Stream_LE(&ConsumerReportData, sizeof(ConsumerReportData), NULL); //Write Keyboard Report Data
		Endpoint_ClearIN(); //Finalize the stream transfer to send the last packet
		memset(&ConsumerReportData, 0, sizeof(ConsumerReportData)); //Clear the report data afterwards
	}
}

void updateFNKeys (void) {
	hasFn = 0;
	for (int i = 0; i < KEYMAP_SIZE; i++) {
		if ((kmMain[i] == 0xFF)&&(hasFn<8)) {
			fnPort [hasFn] = i >> 3;
			fnPin [hasFn] = i & 0x07;
			hasFn++;
		}
	}
}

void updateKeymap(unsigned char *map, int part) {
	if (part == 0) {
		for (int i = 0; i < KEYMAP_SIZE; i++) kmMain [i] = map [i];
	}
	else if (part == 1) {
		for (int i = 0; i < KEYMAP_SIZE; i++) kmMMod [i] = map [i];
	}
	else if (part == 2) {
		for (int i = 0; i < KEYMAP_SIZE; i++) kmFn [i] = map [i];
	}
	else if (part == 3) {
		for (int i = 0; i < KEYMAP_SIZE; i++) kmFMod [i] = map [i];
		updateFNKeys ();
	}
}

void updateKeystat(uint32_t *stat) {
	for (int i = 0; i < KEYMAP_SIZE; i++) {
		kpStat[i] = stat[i];
	}
}

void updateKey(unsigned char key, unsigned char mod, unsigned char fkey, unsigned char fmod, int index) {
	char needUpd = 0;
	if ((kmMain[index] == 0xFF)||(key == 0xFF)) needUpd = 1;
	kmMain[index] = key;
	kmMMod[index] = mod;
	kmFn[index] = fkey;
	kmFMod[index] = fmod;
	if (needUpd) updateFNKeys();
}

void updateNmKey(unsigned char key, unsigned char mod, int index) {
	char needUpd = 0;
	if ((kmMain[index] == 0xFF)||(key == 0xFF)) needUpd = 1;
	kmMain[index] = key;
	kmMMod[index] = mod;
	if (needUpd) updateFNKeys();
}

void updateFnKey(unsigned char key, unsigned char mod, int index) {
	kmFn[index] = key;
	kmFMod[index] = mod;
}

uint8_t readEEKBKey(uint8_t ks, uint8_t km, uint8_t key) {
    uint8_t val1, val2, val3;
    eeprom_read_block(&val1, &(storedMap[ks][km][key]), 1);
    eeprom_read_block(&val2, &(keyPressStatistic[key]), 1);
    eeprom_read_block(&val3, &(macrosData[ks][km][key]), 1);
    return val1 | val2 | val3;
}
