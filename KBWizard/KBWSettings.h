#ifndef KBWSETTINGS_H_INCLUDED
#define KBWSETTINGS_H_INCLUDED
#include <inttypes.h>

#define NO_EEPROM_OPERATION		0
#define READ_INITIAL_VALUES		1
#define READ_KEYSET				2
#define READ_KEYSET_PART		3
#define READ_KEYSET_STATISTIC	4
#define READ_KEYSET_STAT_INIT   5

void initCommon(void);

uint8_t getInitialSensorResolution(void);
void setInitialSensorResolution(uint8_t res);
uint8_t getInitialSensorWorkType(void);
void setInitialSensorWorkType(uint8_t type);

void HID_Task(void);
void ProcessGenericHIDReport(uint8_t* DataArray);
void CreateGenericHIDReport(uint8_t* DataArray);

void UpdateStatus(void);

void processDelayLoad(void);

char startEERead(unsigned short address, unsigned char count, unsigned char task);
unsigned short getCurrentReadAddress (void);
unsigned char getBytesReadLeft (void);
unsigned char *getReadArray (void);
void readEEPROMData (void);

char startEEWrite(unsigned short address, unsigned char count, unsigned char *toWrite);
void writeEEPROMData (void);


#endif // KBWSETTINGS_H_INCLUDED
