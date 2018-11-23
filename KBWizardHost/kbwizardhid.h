#ifndef KBWIZARDHID_H
#define KBWIZARDHID_H

#include "hidapi.h"

class KBWizardHID
{
public:
    KBWizardHID();
    bool open();
    void close ();
    int readData(unsigned char *buffer);
    int sendData(unsigned char *buffer, int len);
    bool isOpen();

protected:
    bool opened;
    hid_device *kbDevice;
};

#endif // KBWIZARDHID_H
