#ifndef KBWKEYBOARD_H_INCLUDED
#define KBWKEYBOARD_H_INCLUDED
#include <inttypes.h>

void scanKeyPressed(void);
void Keyboard_ProcessLEDReport(const uint8_t LEDStatus);
void Keyboard_HID_Task(void);
void Consumer_HID_Task(void);
uint8_t* getKBReportData(void);
uint8_t  getKBReportSize(void);
uint8_t* getConsReportData(void);
uint8_t  getConsReportSize(void);
uint8_t getMouseBtnState(void);
void getKBStatus(uint8_t* dataArray);
void updateKeymap(uint8_t *map, int part);
void updateKeystat(uint32_t *stat);
void updateKey(uint8_t key, uint8_t mod, uint8_t fkey, uint8_t fmod, int index);
void updateNmKey(uint8_t key, uint8_t mod, int index);
void updateFnKey(uint8_t key, uint8_t mod, int index);

uint8_t readEEKBKey(uint8_t ks, uint8_t km, uint8_t key);

#endif // KBWKEYBOARD_H_INCLUDED
