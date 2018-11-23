#ifndef BUTTONSET_H
#define BUTTONSET_H

#include <QWidget>
#include <QPushButton>
#include "kbwizardhid.h"

namespace Ui {
class ButtonSet;
}

class ButtonSet : public QWidget
{
    Q_OBJECT

public:
    explicit ButtonSet(QWidget *parent = 0);
    ~ButtonSet();
    QList<QPushButton*> keySetList();
    bool isRightSide();
    void setRightSide(bool side);
    void setKBWDevice(KBWizardHID *dev);
    KBWizardHID *KBWDevice();
    void setCurrentKeymap(uint8_t **keymap);
    uint8_t **currentKeymap();
    void setKeyPressStatistic(uint32_t *stat);
    uint32_t *keyPressStatistic();

    Q_PROPERTY(bool rightSide READ isRightSide WRITE setRightSide)

public slots:
    void keyClicked();

private:
    Ui::ButtonSet *ui;
    QList<QPushButton*> keyList;
    QList<QPoint> pointPos;
    int buttonSize;
    bool rightSideMap = false;
    KBWizardHID *kbDevice = 0;
    uint8_t  curKeymap[4][40];
    uint32_t keyPressStat[40];
};

#endif // BUTTONSET_H
