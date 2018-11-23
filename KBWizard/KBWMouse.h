#ifndef KBWMOUSE_H_INCLUDED
#define KBWMOUSE_H_INCLUDED
#include <inttypes.h>
void initMouse(void);
uint8_t getModifierForMouse(void);
uint8_t getSensorId(void);
uint8_t getSensorRes(void);
uint8_t getSensorWorkType(void);
void setSensorWorkType(uint8_t type);
uint8_t* getMSReportData(void);
uint8_t  getMSReportSize(void);
void Mouse_HID_Task(void);
void MouseReadSensor(void);
void WriteSPIByte(char adr);
char ReadSPIByte(void);
char ReadSensorValue(char adr);
void WriteSensorValue(char adr, char value);
void SetSensorResolution(unsigned char res);

#endif // KBWMOUSE_H_INCLUDED
