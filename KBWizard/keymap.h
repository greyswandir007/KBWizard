#ifndef KEYMAPCONSTANT
#define KEYMAPCONSTANT

#define KEYMAP_SIZE 40

unsigned char keyMap[KEYMAP_SIZE] EEMEM = {
	//PORTA
	HID_KEYBOARD_SC_EQUAL_AND_PLUS,// = +
	HID_KEYBOARD_SC_CLOSING_BRACKET_AND_CLOSING_BRACE, // ]
	HID_KEYBOARD_SC_NON_US_HASHMARK_AND_TILDE, // `
	HID_KEYBOARD_SC_KEYPAD_ASTERISK, // *
	///////
	HID_KEYBOARD_SC_1_AND_EXCLAMATION, // 1
	HID_KEYBOARD_SC_Q, // Q
	HID_KEYBOARD_SC_A, // A
	HID_KEYBOARD_SC_Z, // Z
	//PORTB // 8
	HID_KEYBOARD_SC_2_AND_AT, // 2
	HID_KEYBOARD_SC_W, // W
	HID_KEYBOARD_SC_S, // S
	HID_KEYBOARD_SC_X, // X
	///////
	HID_KEYBOARD_SC_3_AND_HASHMARK,
	HID_KEYBOARD_SC_E,
	HID_KEYBOARD_SC_D,
	HID_KEYBOARD_SC_C,
	//PORTC // 16
	HID_KEYBOARD_SC_4_AND_DOLLAR,
	HID_KEYBOARD_SC_R,
	HID_KEYBOARD_SC_F,
	HID_KEYBOARD_SC_V,
	///////
	HID_KEYBOARD_SC_5_AND_PERCENTAGE,
	HID_KEYBOARD_SC_T,
	HID_KEYBOARD_SC_G,
	HID_KEYBOARD_SC_B,
	//PORTD // 24
	HID_KEYBOARD_SC_LEFT_GUI,
	HID_KEYBOARD_SC_LEFT_CONTROL,
	HID_KEYBOARD_SC_LEFT_SHIFT,
	HID_KEYBOARD_SC_TAB,
	HID_KEYBOARD_SC_BACKSPACE,
	0,0,0,
	//PORTE // 32
	0,0,0,0, 0,0,
	0, // External Fn
	0  // Set External Event
};
unsigned char keyMapMod[KEYMAP_SIZE] EEMEM = {
	//PORTA // 0
	0,0,0,0, 0,0,0,0,
	//PORTB // 8
	0,0,0,0, 0,0,0,0,
	//PORTC // 16
	0,0,0,0, 0,0,0,0,
	//PORTD // 24
	0,0,0,0, 0,0,0,0,
	//PORTE // 32
	0,0,0,0, 0,0,0,0
};
unsigned char keyMapFn[KEYMAP_SIZE] EEMEM = {
	//PORTA // 0
	HID_KEYBOARD_SC_F12, // F12
	HID_KEYBOARD_SC_PAUSE, // Break
	HID_KEYBOARD_SC_PRINT_SCREEN,
	HID_KEYBOARD_SC_ESCAPE,
	///////
	HID_KEYBOARD_SC_F1,
	HID_KEYBOARD_SC_HOME,
	HID_KEYBOARD_SC_PAGE_UP,
	HID_KEYBOARD_SC_MENU,
	//PORTB // 8
	HID_KEYBOARD_SC_F2,
	HID_KEYBOARD_SC_HOME,
	HID_KEYBOARD_SC_LEFT_ARROW,
	HID_KEYBOARD_SC_MEDIA_PLAY,
	///////
	HID_KEYBOARD_SC_F3,
	HID_KEYBOARD_SC_UP_ARROW,
	HID_KEYBOARD_SC_DOWN_ARROW,
	HID_KEYBOARD_SC_MEDIA_STOP,
	//PORTC // 16
	HID_KEYBOARD_SC_F4,
	HID_KEYBOARD_SC_END,
	HID_KEYBOARD_SC_RIGHT_ARROW,
	HID_KEYBOARD_SC_MEDIA_NEXT_TRACK,
	///////
	HID_KEYBOARD_SC_F4,
	HID_KEYBOARD_SC_END,
	HID_KEYBOARD_SC_PAGE_DOWN,
	HID_KEYBOARD_SC_MEDIA_PREVIOUS_TRACK,
	//PORTD	 // 24
	HID_KEYBOARD_SC_LEFT_GUI,
	HID_KEYBOARD_SC_LEFT_CONTROL,
	HID_KEYBOARD_SC_LEFT_SHIFT,
	HID_KEYBOARD_SC_INSERT,
	HID_KEYBOARD_SC_DELETE,
	0,0,0,
	//PORTE // 32
	0,0,0,0, 0,0,
	0, // External Fn
	0  // Set External Event
};
unsigned char keyMapFnMod[KEYMAP_SIZE] EEMEM = {
	//PORTA // 0
	0,0,0,0,
	0,HID_KEYBOARD_MODIFIER_LEFTCTRL,0,0,
	//PORTB // 8
	0,0,0,0, 0,0,0,0,
	//PORTC // 16
	0,0,0,0,
        0,HID_KEYBOARD_MODIFIER_LEFTCTRL,0,0,
	//PORTD // 24
	0,0,0,0, 0,0,0,0,
	//PORTE // 32
	0,0,0,0, 0,0,0,0
};
#endif //KEYMAPCONSTANT