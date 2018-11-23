#include "buttonset.h"
#include "ui_buttonset.h"

ButtonSet::ButtonSet(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ButtonSet)
{
    for (int j = 0; j < 4; j++) {
        for (int i = 0; i < 40; i++) curKeymap[j][i] = 0;
    }
    for (int i = 0; i < 40; i++) keyPressStat[i] = 0;
    buttonSize = 50;
    pointPos << QPoint(290,20) << QPoint(290,70) << QPoint(290,120) << QPoint(290,170);
    pointPos << QPoint(240,20) << QPoint(240,70) << QPoint(240,120) << QPoint(240,170);
    pointPos << QPoint(190,20) << QPoint(190,70) << QPoint(190,120) << QPoint(190,170);
    pointPos << QPoint(140,20) << QPoint(140,70) << QPoint(140,120) << QPoint(140,170);
    pointPos << QPoint(90,20) << QPoint(90,70) << QPoint(90,120) << QPoint(90,170);
    pointPos << QPoint(40,20) << QPoint(40,70) << QPoint(40,120) << QPoint(40,170);

    pointPos << QPoint(170, 350) << QPoint(220,350) << QPoint(270, 350) << QPoint(100,310);
    pointPos << QPoint(160, 280) << QPoint(210,280) << QPoint(260, 280) << QPoint(310,280);
    pointPos << QPoint(240, 220) << QPoint(190,220) << QPoint(140, 220) << QPoint(90,220);
    pointPos << QPoint(40, 280) << QPoint(50,410) << QPoint(120, 410) << QPoint(190,410);
    ui->setupUi(this);
    for (int i = 0; i < pointPos.count(); i++) {
        QPushButton *btn;
        btn = new QPushButton(this);
        btn->setGeometry(pointPos.at(i).x(),pointPos.at(i).y(), buttonSize, buttonSize);
        btn->setText(QString("/%1\\").arg(i+1));
        keyList.append(btn);
        connect(btn,SIGNAL(clicked()),this,SLOT(keyClicked()));
    }
}

ButtonSet::~ButtonSet()
{
    delete ui;
}

QList<QPushButton *> ButtonSet::keySetList()
{
    return keyList;
}

bool ButtonSet::isRightSide()
{
    return rightSideMap;
}

void ButtonSet::setRightSide(bool side)
{
    if (rightSideMap != side)  {
        rightSideMap = side;
        if (rightSideMap) {
            for (int i = 0; i < pointPos.count(); i++) {
                keyList[i]->setGeometry(this->geometry().width() - pointPos.at(i).x()-40,pointPos.at(i).y(), buttonSize, buttonSize);
            }
        }
        else {
            for (int i = 0; i < pointPos.count(); i++) {
                keyList[i]->setGeometry(pointPos.at(i).x(),pointPos.at(i).y(), buttonSize, buttonSize);
            }
        }
    }
}

void ButtonSet::setKBWDevice(KBWizardHID *dev)
{
    kbDevice = dev;
}

KBWizardHID *ButtonSet::KBWDevice()
{
    return kbDevice;
}

void ButtonSet::setCurrentKeymap(uint8_t **keymap)
{
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 40; j++)
            curKeymap[i][j] = keymap[i][j];
    }
}

uint8_t **ButtonSet::currentKeymap()
{
    return (uint8_t **)curKeymap;
}

void ButtonSet::setKeyPressStatistic(uint32_t *stat)
{
    for (int i = 0; i < 40; i++)
        keyPressStat[i] = stat[i];
}

uint32_t *ButtonSet::keyPressStatistic()
{
    return keyPressStat;
}

void ButtonSet::keyClicked()
{

}
