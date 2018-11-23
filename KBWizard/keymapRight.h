#ifndef KEYMAPCONSTANT
#define KEYMAPCONSTANT

#define KEYMAP_SIZE 40
#define KEYMAP_READ_SIZE 10
#define KEYMAP_COUNT 10
#define MAIN_KEY_MAP 0
#define MAIN_KEY_MOD 1
#define FN_KEY_MAP 2
#define FN_KEY_MOD 3

#define NONHID_KEYBOARD_SC_MAIL			0xEC
#define NONHID_MOUSE_LEFT_BUTTON		0xF5

//0xA5-AF Undefined HID
//0xDE 0xDF Undefined HID
//0xF5-F7 Undefined HID
//0xFC 0xFD 0xFE 0xFF

//MyKeys
//0xDE - Change Lang
//0xDF - Change KeyMap
//0xEC - Mail
//0xF5 - Mouse LBtn
//0xF6 - Mouse RBtn
//0xF7 - MOuse MBtn
//0xFC - WWW Favorite
//0xFD - Wake

//0xFF - Fn


unsigned char EEMEM storedMap[KEYMAP_COUNT][4][KEYMAP_SIZE] = {
	{{
		//PORTA
		HID_KEYBOARD_SC_6_AND_CARET,// 6
		HID_KEYBOARD_SC_Y, // y
		HID_KEYBOARD_SC_H, // H
		HID_KEYBOARD_SC_N, // N
		///////
		HID_KEYBOARD_SC_7_AND_AMPERSAND, // 7
		HID_KEYBOARD_SC_U, // U
		HID_KEYBOARD_SC_J, // J
		HID_KEYBOARD_SC_M, // M
		//PORTC // 8
		HID_KEYBOARD_SC_8_AND_ASTERISK, // 2
		HID_KEYBOARD_SC_I, // I
		HID_KEYBOARD_SC_K, // K
		HID_KEYBOARD_SC_COMMA_AND_LESS_THAN_SIGN, // .
		///////
		HID_KEYBOARD_SC_9_AND_OPENING_PARENTHESIS,
		HID_KEYBOARD_SC_O,
		HID_KEYBOARD_SC_L,
		HID_KEYBOARD_SC_DOT_AND_GREATER_THAN_SIGN,
		//PORTD // 16
		HID_KEYBOARD_SC_0_AND_CLOSING_PARENTHESIS,
		HID_KEYBOARD_SC_P,
		HID_KEYBOARD_SC_SEMICOLON_AND_COLON,
		HID_KEYBOARD_SC_SLASH_AND_QUESTION_MARK,
		///////
		HID_KEYBOARD_SC_MINUS_AND_UNDERSCORE,
		HID_KEYBOARD_SC_OPENING_BRACKET_AND_OPENING_BRACE,
		HID_KEYBOARD_SC_APOSTROPHE_AND_QUOTE,
		HID_KEYBOARD_SC_BACKSLASH_AND_PIPE,
		//PORTE // 24
		0xF5,  //Mouse LBTN
		HID_KEYBOARD_SC_RIGHT_ALT,
		0xFF, //Fn
		HID_KEYBOARD_SC_ENTER,
		HID_KEYBOARD_SC_SPACE,
		0,0,0,
		//PORTF // 32
		0,0,0,0, 0,0,0,0
	},
	{
		//PORTA // 0
		0,0,0,0, 0,0,0,0,
		//PORTC // 8
		0,0,0,0, 0,0,0,0,
		//PORTD // 16
		0,0,0,0, 0,0,0,0,
		//PORTE // 24
		0,0,0,0, 0,0,0,0,
		//PORTF // 32
		0,0,0,0, 0,0,0,0
	},
	{
		//PORTA // 0
		HID_KEYBOARD_SC_F6, // F12
		HID_KEYBOARD_SC_Y, // y
		HID_KEYBOARD_SC_H, // H
		HID_KEYBOARD_SC_N, // N
		///////
		HID_KEYBOARD_SC_F7,
		HID_KEYBOARD_SC_MEDIA_VOLUME_UP,//HID_KEYBOARD_SC_MEDIA_VOLUME_UP,
		HID_KEYBOARD_SC_PAGE_UP,
		HID_KEYBOARD_SC_MINUS_AND_UNDERSCORE, // M
		//PORTC // 8
		HID_KEYBOARD_SC_F8,
		HID_KEYBOARD_SC_I, // I
		HID_KEYBOARD_SC_LEFT_ARROW, //
		HID_KEYBOARD_SC_MINUS_AND_UNDERSCORE, //
		///////
		HID_KEYBOARD_SC_F9,
		HID_KEYBOARD_SC_UP_ARROW,
		HID_KEYBOARD_SC_DOWN_ARROW,
		HID_KEYBOARD_SC_EQUAL_AND_PLUS,
		//PORTD // 16
		HID_KEYBOARD_SC_F10,
		HID_KEYBOARD_SC_P,
		HID_KEYBOARD_SC_RIGHT_ARROW,
		HID_KEYBOARD_SC_EQUAL_AND_PLUS,
		///////
		HID_KEYBOARD_SC_F11,
		HID_KEYBOARD_SC_MEDIA_VOLUME_DOWN,//HID_KEYBOARD_SC_MEDIA_VOLUME_DOWN,
		HID_KEYBOARD_SC_PAGE_DOWN,
		HID_KEYBOARD_SC_BACKSLASH_AND_PIPE,
		//PORTE	 // 24
		0xF6,  //Mouse RBTN
		HID_KEYBOARD_SC_RIGHT_ALT,
		0xFF, // Fn
		0xFD, // Select keymap
		0xFE, // Change lang
		0,0,0,
		//PORTF // 32
		0,0,0,0, 0,0,0,0
	},
	{
		//PORTA // 0
		0,0,0,0,
		0,0,HID_KEYBOARD_MODIFIER_RIGHTCTRL,0,
		//PORTC // 8
		0,0,HID_KEYBOARD_MODIFIER_RIGHTCTRL,HID_KEYBOARD_MODIFIER_RIGHTSHIFT,
		0,HID_KEYBOARD_MODIFIER_RIGHTCTRL,HID_KEYBOARD_MODIFIER_RIGHTCTRL,0,
		//PORTD // 16
		0,0,HID_KEYBOARD_MODIFIER_RIGHTCTRL,HID_KEYBOARD_MODIFIER_RIGHTSHIFT,
			0,0,HID_KEYBOARD_MODIFIER_RIGHTCTRL,0,
		//PORTE // 24
		0,0,0,0, 0,0,0,0,
		//PORTF // 32
		0,0,0,0, 0,0,0,0
	}}
};

uint32_t keyPressStatistic[KEYMAP_SIZE] EEMEM = {0};

#endif //KEYMAPCONSTANT
