#ifndef USBCOMMAND_H_INCLUDED
#define USBCOMMAND_H_INCLUDED

#define KBW_VERSION					0x01
//Commands
#define KBW_STATUS					0x00
#define KBW_SET_SENSOR_RESOLUTION	0x01
#define KBW_GET_EEPROM_KB_KEY		0x02 //4 byte at time
#define KBW_SET_EEPROM_KB_KEY		0x03 //4 byte at time
#define KBW_SET_KEYMAP				0x04
#define KBW_UPDATE_KEYMAP			0x05
#define KBW_SET_SENSOR_WORK_TYPE	0x06
#define KBW_GET_SENSOR_WORK_TYPE	0x07
#define KBW_GET_KEY_PRESS_STATISTIC	0x08
#define KBW_UPDATE_EEPROM_KEY		0x09
#define KBW_GET_CURRENT_KEY_STATE	0x0A

#define KBW_READ_RESERVED			0xEF

//Sensor modes
#define KBW_SENSOR_MODE_NORMAL		0x00
#define KBW_SENSOR_MODE_WHEEL		0x01

#define KBW_SENSOR_MODE_WITH_LBTN	0x02
#define KBW_SENSOR_MODE_WITH_RBTN	0x04
#define KBW_SENSOR_MODE_WITH_MBTN	0x08
#define KBW_SENSOR_MODE_WITH_CTRL	0x10
#define KBW_SENSOR_MODE_WITH_SHIFT	0x20
#define KBW_SENSOR_MODE_WITH_ALT	0x40
#define KBW_SENSOR_MODE_WITH_META	0x80

#endif // USBCOMMAND_H_INCLUDED