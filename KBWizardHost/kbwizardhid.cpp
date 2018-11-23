#include "kbwizardhid.h"
#include <QString>
#include <QDebug>

KBWizardHID::KBWizardHID()
{
    opened = false;
    kbDevice = 0;
}

bool KBWizardHID::open()
{
    if (!opened) {
        unsigned int vid = 0x1209, pid = 0x411D;
        hid_device_info *info;
        hid_init();
        info = hid_enumerate(vid, pid);
        if (info) {
            qDebug() << info->product_string << info->path << info->interface_number << info->serial_number;
            while(info->next&&(info->interface_number != 3)) {
                qDebug() << info->product_string << info->path << info->interface_number << info->serial_number;
                info = info->next;
            }
            if (info&&info->interface_number == 3) {
                qDebug() << info->product_string << info->path << info->interface_number << info->serial_number;
                kbDevice = hid_open_path(info->path);
            }
        }
        if (kbDevice) opened = true;
    }
    return opened;
}

void KBWizardHID::close()
{
    if (kbDevice) hid_close(kbDevice);
    kbDevice = 0;
    hid_exit();
    opened = false;
}

int KBWizardHID::readData(unsigned char *buffer)
{
    int len = 0;
    if (kbDevice) {
        len = hid_read_timeout(kbDevice, buffer, 8, 1000);
    }
    return len;
}

int KBWizardHID::sendData(unsigned char *buffer, int len)
{
    //bool result = false;
    int slen = 0;
    if (kbDevice) {
        slen = hid_write(kbDevice, (unsigned char*)buffer, len);
        //if(slen != len) {
        //    qDebug() << "Failed: bulk transfer for write failed";
        //}
        //else {
        //    result = true;
        //}
        //const wchar_t *err = hid_error(kbDevice);
        //if (err)
        //    qDebug() << QString::fromStdWString(err);
        //qDebug() << "write length" << slen;
    }
    //return result;
    return slen;
}

bool KBWizardHID::isOpen()
{
    return opened;
}
