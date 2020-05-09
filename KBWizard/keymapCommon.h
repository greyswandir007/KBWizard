#ifndef KEYMAP_COMMON
#define KEYMAP_COMMON

#define KEYMAP_SIZE 40
#define KEYMAP_READ_SIZE 10
#define KEYMAP_COUNT 10
#define MAIN_KEY_MAP 0
#define MAIN_KEY_MOD 1
#define FN_KEY_MAP 2
#define FN_KEY_MOD 3

#define NONHID_CHANGE_LANG			0xDE
#define NONHID_CHANGE_KEYMAP			0xDF
#define NONHID_KEYBOARD_SC_MAIL			0xEC
#define NONHID_MOUSE_LEFT_BUTTON		0xF5
#define NONHID_MOUSE_RIGHT_BUTTON		0xF6
#define NONHID_MOUSE_MIDDLE_BUTTON		0xF7
#define NONHID_WWW_FAVORITE			0xFC
#define NONHID_WAKE				0xFD
#define NONHID_BLOCK_KEYBOARD			0xFE
#define NONHID_FN_KEY				0xFF

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

#endif //KEYMAP_COMMON
