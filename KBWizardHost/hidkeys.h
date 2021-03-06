#ifndef HIDKEYS_H
#define HIDKEYS_H
#include <QString>

QString keyCategory[10] = {
    "Letters", //4-29
    "Numbers", //30-39
    "Functonal", //40-44,57,70-83,101,102,116-132,153-164
    "Math",//45-56,100,178-181
    "F?",//58-69,104-115
    "Lang", //135-152
    "Modifier",//224-231
    "Media",//232-244, 248-251
    "Keypad",//84-99,103,133,134,176,177,182-221
    "Special"//252-255
};//4-29,30-39,40-44,45-56,57,58-69,70-83,84-99,100,101,102,103,104-115,
//116-132,133,134,135-152,153-164,(165-175),176,177,178-181,182-221,(222,223),224-231,232-244,(245-247),248-251,[252-255]

QString keyNames[] ={
"",//0
"ERROR_ROLLOVER",//1
"POST_FAIL",//2
"ERROR_UNDEFINED",//3
"A",
"B",
"C",
"D",
"E",
"F",
"G",
"H",
"I",
"J",
"K",
"L",
"M",
"N",
"O",
"P",
"Q",
"R",
"S",
"T",
"U",
"V",
"W",
"X",
"Y",
"Z",
"1",//_AND_EXCLAMATION
"2",//_AND_AT
"3",//_AND_HASHMARK
"4",//_AND_DOLLAR
"5",//_AND_PERCENTAGE
"6",//_AND_CARET
"7",//_AND_AMPERSAND
"8",//_AND_ASTERISK
"9",//_AND_OPENING_PARENTHESIS
"0",//_AND_CLOSING_PARENTHESIS
"ENTER",//
"ESC",//
"<-",//
"-->|",//
"SPACE",//
"-",//_AND_UNDERSCORE
"=",//_AND_PLUS
"[",//_AND_OPENING_B
"]",//_AND_CLOSING_B
"\\",//_AND_PIPE
"`",//_AND_TILDE
";",//_AND_COLON
"'",//_AND_QUOTE
"`",//_AND_TILDE
",",//_AND_LESS_THAN_SIGN
".",//_AND_GREATER_THAN_SIGN
"/",//_AND_QUESTION_MARK
"CAPS_LOCK",//
"F1",//
"F2",//
"F3",//
"F4",//
"F5",//
"F6",//
"F7",//
"F8",//
"F9",//
"F10",//
"F11",//
"F12",//
"PRINT_SCREEN",//
"SCROLL_LOCK",//
"PAUSE",//
"INSERT",//
"HOME",//
"PG_UP",//
"DEL",//
"END",//
"PG_DN",//
"R_ARR",//
"L_ARR",//
"D_ARR",//
"U_ARR",//
"NUM_LOCK",//
"KEYPAD_/",//
"KEYPAD_*",//
"KEYPAD_-",//
"KEYPAD_+",//
"KEYPAD_ENTER",//
"KEYPAD_1",//_AND_END
"KEYPAD_2",//_AND_DOWN_ARROW
"KEYPAD_3",//_AND_PAGE_DOWN
"KEYPAD_4",//_AND_LEFT_ARROW
"KEYPAD_5",//
"KEYPAD_6",//_AND_RIGHT_ARROW
"KEYPAD_7",//_AND_HOME
"KEYPAD_8",//_AND_UP_ARROW
"KEYPAD_9",//_AND_PAGE_UP
"KEYPAD_0",//_AND_INSERT
"KEYPAD_.",//_AND_DELETE
"\\",//_AND_PIPE
"APP",//
"POWER",//
"KEYPAD_=",//_SIGN
"F13",//
"F14",//
"F15",//
"F16",//
"F17",//
"F18",//
"F19",//
"F20",//
"F21",//
"F22",//
"F23",//
"F24",//
"EXECUTE",//
"HELP",//
"MENU",//
"SELECT",//
"STOP",//
"AGAIN",//
"UNDO",//
"CUT",//
"COPY",//
"PASTE",//
"FIND",//
"MUTE",//
"VOL_UP",//
"VOL_DN",//
"LOCKING_CAPS_LOCK",//
"LOCKING_NUM_LOCK",//
"LOCKING_SCROLL_LOCK",//
"KEYPAD_,",//
"KEYPAD_=_AS400",//
"INTERNATIONAL1",//
"INTERNATIONAL2",//
"INTERNATIONAL3",//
"INTERNATIONAL4",//
"INTERNATIONAL5",//
"INTERNATIONAL6",//
"INTERNATIONAL7",//
"INTERNATIONAL8",//
"INTERNATIONAL9",//
"LANG1",//
"LANG2",//
"LANG3",//
"LANG4",//
"LANG5",//
"LANG6",//
"LANG7",//
"LANG8",//
"LANG9",//
"ALTER_ERASE",//
"SYSREQ",//
"CANCEL",//
"CLEAR",//
"PRIOR",//
"RETURN",//
"SEPARATOR",//
"OUT",//
"OPER",//
"CLEAR_AND_AGAIN",//
"CRSEL_AND_PROPS",//
"EXSEL",//
"",//165
"",//166
"",//167
"",//168
"",//169
"",//170
"",//171
"",//172
"",//173
"",//174
"",//175
"KEYPAD_00",//
"KEYPAD_000",//
"THOUSANDS_SEPARATOR",//
"DECIMAL_SEPARATOR",//
"CURRENCY_UNIT",//
"CURRENCY_SUB_UNIT",//
"KEYPAD_(",//
"KEYPAD_)",//
"KEYPAD_[",//
"KEYPAD_]",//
"KEYPAD_TAB",//
"KEYPAD_BACKSPACE",//
"KEYPAD_A",//
"KEYPAD_B",//
"KEYPAD_C",//
"KEYPAD_D",//
"KEYPAD_E",//
"KEYPAD_F",//
"KEYPAD_XOR",//
"KEYPAD_CARET",//
"KEYPAD_%",//
"KEYPAD_<",//
"KEYPAD_>",//
"KEYPAD_&",//
"KEYPAD_&&",//
"KEYPAD_|",//
"KEYPAD_||",//
"KEYPAD_,",//
"KEYPAD_HASHMARK",//
"KEYPAD_SPACE",//
"KEYPAD_AT",//
"KEYPAD_EXCLAMATION_SIGN",//
"KEYPAD_MEMORY_STORE",//
"KEYPAD_MEMORY_RECALL",//
"KEYPAD_MEMORY_CLEAR",//
"KEYPAD_MEMORY_+",//
"KEYPAD_MEMORY_-",//
"KEYPAD_MEMORY_*",//
"KEYPAD_MEMORY_/",//
"KEYPAD_+-",//
"KEYPAD_CLEAR",//
"KEYPAD_CLEAR_ENTRY",//
"KEYPAD_BINARY",//
"KEYPAD_OCTAL",//
"KEYPAD_DECIMAL",//
"KEYPAD_HEXADECIMAL",//
"",//222
"",//223
"LCTRL",//
"LSHIFT",//
"LALT",//
"LGUI",//
"RCTRL",//
"RSHIFT",//
"RALT",//
"RGUI",//
"MEDIA_PLAY",//
"MEDIA_STOP",//
"MEDIA_PREVIOUS_TRACK",//
"MEDIA_NEXT_TRACK",//
"MEDIA_EJECT",//
"MEDIA_VOL_UP",//
"MEDIA_VOL_DOWN",//
"MEDIA_MUTE",//
"MEDIA_WWW",//
"MEDIA_BACKWARD",//
"MEDIA_FORWARD",//
"MEDIA_CANCEL",//
"MEDIA_SEARCH",//
"",//245
"",//246
"",//247
"MEDIA_SLEEP",//
"MEDIA_LOCK",//
"MEDIA_RELOAD",//
"MEDIA_CALCULATOR",//
"Keymap",//252
"Ch lang",//253
"Mouse",//254
"Fn"//255
};

#endif // HIDKEYS_H
