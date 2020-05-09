QT       += core gui widgets

CONFIG += c++2a

TARGET = KBWizardHost
TEMPLATE = app

DEFINES += QT_DEPRECATED_WARNINGS

SOURCES += main.cpp\
        mainwindow.cpp \
    kbwizardhid.cpp \
    buttonset.cpp

win32:SOURCES += hid.c
linux:!android{
        SOURCES += hid_linux.c
}
macx:SOURCES += hid_mac.c
android: SOURCES += hid_libusb.c

HEADERS  += mainwindow.h \
    hidapi.h \
    kbwizardhid.h \
    hidkeys.h \
    buttonset.h

FORMS    += mainwindow.ui \
    buttonset.ui

win32:LIBS += -lhid -lsetupapi
unix:LIBS += -lusb
