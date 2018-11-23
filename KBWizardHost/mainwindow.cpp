#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include "hidkeys.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow) {
    for (int j = 0; j < 4; j++) {
        for (int i = 0; i < 40; i++) {
           rightKeymap[j][i] = 0; // keyMap
        }
    }
    for (int j = 0; j < 4; j++) {
        for (int i = 0; i < 40; i++) {
           leftKeymap[j][i] = 0; // keyMap
        }
    }
    for (int i = 0; i < 40; i++) {
        rightKeyStat[i] = 0;
    }
    for (int i = 0; i < 40; i++) {
        leftKeyStat[i] = 0;
    }
    for (int i = 0; i < 10; i++) {
        keyCategories cat;
        cat.name = keyCategory[i];
        keyCat.append(cat);
    }
    for (int i = 4; i <= 29; i++)
        keyCat[0].indexes.append(i);
    for (int i = 30; i <= 39; i++)
        keyCat[1].indexes.append(i);
    for (int i = 40; i <= 44; i++)
        keyCat[2].indexes.append(i);
    keyCat[2].indexes.append(57);
    for (int i = 70; i <= 83; i++)
        keyCat[2].indexes.append(i);
    keyCat[2].indexes.append(101);
    keyCat[2].indexes.append(102);
    for (int i = 116; i <= 132; i++)
        keyCat[2].indexes.append(i);
    for (int i = 153; i <= 164; i++)
        keyCat[2].indexes.append(i);
    for (int i = 45; i <= 56; i++)
        keyCat[3].indexes.append(i);
    keyCat[3].indexes.append(100);
    for (int i = 178; i <= 181; i++)
        keyCat[3].indexes.append(i);
    for (int i = 58; i <= 69; i++)
        keyCat[4].indexes.append(i);
    for (int i = 104; i <= 115; i++)//58-69,104-115
        keyCat[4].indexes.append(i);
    for (int i = 135; i <= 152; i++)//135-152
        keyCat[5].indexes.append(i);
    for (int i = 224; i <= 231; i++)//224-231
        keyCat[6].indexes.append(i);
    for (int i = 232; i <= 244; i++)//232-244, 248-251
        keyCat[7].indexes.append(i);
    for (int i = 248; i <= 251; i++)
        keyCat[7].indexes.append(i);
    for (int i = 84; i <= 99; i++)//84-99,103,133,134,176,177,182-221
        keyCat[8].indexes.append(i);
    keyCat[8].indexes.append(103);
    keyCat[8].indexes.append(133);
    keyCat[8].indexes.append(134);
    keyCat[8].indexes.append(176);
    keyCat[8].indexes.append(177);
    for (int i = 182; i <= 221; i++)
        keyCat[8].indexes.append(i);
    for (int i = 252; i <= 255; i++)//252-255
        keyCat[9].indexes.append(i);
    delayReadKeyPos = 0;
    delayReadKeyMap = 0;
    delayReadKeySet = 0;
    ui->setupUi(this);
    connect(&timer1,SIGNAL(timeout()),this,SLOT(timedEvent()));
    connect(&readKeyTimer,SIGNAL(timeout()),this,SLOT(readKeysetEvent()));
    connect(&updateKeyTimer,SIGNAL(timeout()),this,SLOT(updateKeysetEvent()));
    connect(&updateStateTimer,SIGNAL(timeout()),this,SLOT(updateStateEvent()));
    rightSideList.append(ui->keyR01);
    rightSideList.append(ui->keyR02);
    rightSideList.append(ui->keyR03);
    rightSideList.append(ui->keyR04);
    rightSideList.append(ui->keyR05);
    rightSideList.append(ui->keyR06);
    rightSideList.append(ui->keyR07);
    rightSideList.append(ui->keyR08);
    rightSideList.append(ui->keyR09);
    rightSideList.append(ui->keyR10);
    rightSideList.append(ui->keyR11);
    rightSideList.append(ui->keyR12);
    rightSideList.append(ui->keyR13);
    rightSideList.append(ui->keyR14);
    rightSideList.append(ui->keyR15);
    rightSideList.append(ui->keyR16);
    rightSideList.append(ui->keyR17);
    rightSideList.append(ui->keyR18);
    rightSideList.append(ui->keyR19);
    rightSideList.append(ui->keyR20);
    rightSideList.append(ui->keyR21);
    rightSideList.append(ui->keyR22);
    rightSideList.append(ui->keyR23);
    rightSideList.append(ui->keyR24);
    rightSideList.append(ui->keyR25);
    rightSideList.append(ui->keyR26);
    rightSideList.append(ui->keyR27);
    rightSideList.append(ui->keyR28);
    rightSideList.append(ui->keyR29);
    rightSideList.append(ui->keyR30);
    rightSideList.append(ui->keyR31);
    rightSideList.append(ui->keyR32);
    rightSideList.append(ui->keyR33);
    rightSideList.append(ui->keyR34);
    rightSideList.append(ui->keyR35);
    rightSideList.append(ui->keyR36);
    rightSideList.append(ui->keyR37);
    rightSideList.append(ui->keyR38);
    rightSideList.append(ui->keyR39);
    rightSideList.append(ui->keyR40);
    leftSideList.append(ui->keyL01);
    leftSideList.append(ui->keyL02);
    leftSideList.append(ui->keyL03);
    leftSideList.append(ui->keyL04);
    leftSideList.append(ui->keyL05);
    leftSideList.append(ui->keyL06);
    leftSideList.append(ui->keyL07);
    leftSideList.append(ui->keyL08);
    leftSideList.append(ui->keyL09);
    leftSideList.append(ui->keyL10);
    leftSideList.append(ui->keyL11);
    leftSideList.append(ui->keyL12);
    leftSideList.append(ui->keyL13);
    leftSideList.append(ui->keyL14);
    leftSideList.append(ui->keyL15);
    leftSideList.append(ui->keyL16);
    leftSideList.append(ui->keyL17);
    leftSideList.append(ui->keyL18);
    leftSideList.append(ui->keyL19);
    leftSideList.append(ui->keyL20);
    leftSideList.append(ui->keyL21);
    leftSideList.append(ui->keyL22);
    leftSideList.append(ui->keyL23);
    leftSideList.append(ui->keyL24);
    leftSideList.append(ui->keyL25);
    leftSideList.append(ui->keyL26);
    leftSideList.append(ui->keyL27);
    leftSideList.append(ui->keyL28);
    leftSideList.append(ui->keyL29);
    leftSideList.append(ui->keyL30);
    leftSideList.append(ui->keyL31);
    leftSideList.append(ui->keyL32);
    leftSideList.append(ui->keyL33);
    leftSideList.append(ui->keyL34);
    leftSideList.append(ui->keyL35);
    leftSideList.append(ui->keyL36);
    leftSideList.append(ui->keyL37);
    leftSideList.append(ui->keyL38);
    leftSideList.append(ui->keyL39);
    leftSideList.append(ui->keyL40);
    for (int i = 0; i < 40; i++) {
        connect(rightSideList[i],SIGNAL(clicked()),this,SLOT(keyClicked()));
        connect(leftSideList[i],SIGNAL(clicked()),this,SLOT(keyClicked()));
    }
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::readState() {
    unsigned char buf[32];
    for (int i = 0; i < 9; i++) buf[i] = 0;
    kbDevice.sendData(buf,9);
    int len = kbDevice.readData(buf);
    if (len) {
        QString resolution[] = {"No resolution", "125 cpi", "250 cpi", "375 cpi", "500 cpi", "675 cpi", "750 cpi",
                               "875 cpi", "1000 cpi", "1125 cpi", "1250 cpi", "1375 cpi"};

        QString str = "Readed data ";
        for(int i = 0; i < len; i++) {
            str += QString("0x%1 ").arg((unsigned int)(buf[i]),2,16,QChar('0'));
        }
        if (buf[0] == 0x4B) {
            str += "\n";str += buf[0]; str += buf[1]; str += buf[2]; str += "\n";
            if (buf[3] == 'R') str += "Right part\n";
            else if (buf[3] == 'L') str += "Left part\n";
            str += QString("Current keymap: %1\n").arg((unsigned short)buf[4]);
            str += QString("Sensor device Id: %1\n").arg((unsigned int)buf[5],2,16,QChar('0'));
            int res = buf[6] & 0x0F;
            if ((res < 0)||(res > 11)) res = 0;
            str += QString("Current resolution: %1\n").arg(resolution[res]);
            str += QString("Device version: %1\n").arg((unsigned int)buf[7],2,16,QChar('0'));
            ui->textEdit->setText(str);
        }
        else ui->textEdit->append(str);
    }
}

void MainWindow::on_openButton_clicked() {
    if (kbDevice.open()) ui->statusLabel->setText("Connected");
    else ui->statusLabel->setText("Disconnected");
    firstRead = true;
}

void MainWindow::on_closeButton_clicked() {
    kbDevice.close();
    ui->statusLabel->setText("Disconnected");
}

void MainWindow::on_readButton_clicked() {
    unsigned char buf[32];
    int len = kbDevice.readData(buf);
    if (len) {
        QString str = "Readed data ";
        for(int i = 0; i < len; i++) {
            str += QString("0x%1 ").arg((unsigned int)(buf[i]),2,16,QChar('0'));
        }
        ui->textEdit->append(str);
    }
}

void MainWindow::on_autoReadButton_clicked() {
    if (timer1.isActive()) timer1.stop();
    else timer1.start(100);
}

void MainWindow::timedEvent() {
    readState();
}

void MainWindow::readKeysetEvent() {
    unsigned char buf[32];
    int len = kbDevice.readData(buf);
    if (len) {
        if ((buf[0] == 0x52)&&(buf[1] == delayReadKeySet)&&(buf[2] == delayReadKeyMap)&&(buf[3] == delayReadKeyPos)) {
            rightKeymap[delayReadKeyMap][delayReadKeyPos] = buf[4];
            rightKeymap[delayReadKeyMap][delayReadKeyPos+1] = buf[5];
            rightKeymap[delayReadKeyMap][delayReadKeyPos+2] = buf[6];
            rightKeymap[delayReadKeyMap][delayReadKeyPos+3] = buf[7];
            rightSideList[delayReadKeyPos]->setText(keyText(delayReadKeyPos));
            rightSideList[delayReadKeyPos+1]->setText(keyText(delayReadKeyPos+1));
            rightSideList[delayReadKeyPos+2]->setText(keyText(delayReadKeyPos+2));
            rightSideList[delayReadKeyPos+3]->setText(keyText(delayReadKeyPos+3));
            delayReadKeyPos += 4;
            float progress = ((delayReadKeyMap*40+delayReadKeyPos)/160.0)*100;
            ui->progressBar->setValue((int)progress);
            if (delayReadKeyPos >= 40) {
                delayReadKeyPos = 0;
                delayReadKeyMap++;
                if (delayReadKeyMap >= 4) {
                    readKeyTimer.stop();
                    ui->progressBar->setValue(100);
                }
            }
            for (int i = 0; i < 9; i++) buf[i] = 0;
            buf[1] = 0x02;//Read EEPROM
            buf[2] = delayReadKeySet;
            buf[3] = delayReadKeyMap;
            buf[4] = delayReadKeyPos;
            kbDevice.sendData(buf,9);
        }
    }
}

void MainWindow::updateKeysetEvent()
{
    unsigned char buf[32];
    int len = kbDevice.readData(buf);
    if (len) {
        if ((buf[0] != 'B')&&(buf[0]!=0xFF)) {
        //keysToUpdateLeft;
            if (keysToUpdateRight.count()>0) {
                for (int i = 0; i < 9; i++) buf[i] = 0;
                buf[1] = 0x09;//Update key EEPROM
                buf[2] = delayReadKeySet;
                buf[3] = ui->comboBox->currentIndex()*2;
                buf[4] = keysToUpdateRight.at(0);
                buf[5] = rightKeymap[buf[3]][buf[4]];
                buf[6] = rightKeymap[buf[3]+1][buf[4]];
                kbDevice.sendData(buf,9);
                keysToUpdateRight.removeAt(0);
            }
            else {
                updateKeyTimer.stop();
            }
        }
    }
}

void MainWindow::updateStateEvent() {
    unsigned char buf[32];
    int len = kbDevice.readData(buf);
    if (len) {
        if ((buf[0] == 0x50)||(buf[0] == 0x70)) {
            int k = 0;
            qDebug() << buf[1] << buf[2] << buf[3] << buf[4] << buf[5] << buf[6] << buf[7];
            if (buf[0] == 0x50) ui->comboBox->setCurrentIndex(1);
            else ui->comboBox->setCurrentIndex(0);
            for(int i = 0; i < 5; i++) {
                for (int j = 0; j < 8; j++) {
                   if (buf[i+1] & (1 << j)) {
                       rightSideList[k]->setChecked(true);
                       rightSideList[k]->setCheckable(true);
                   }
                   else {
                       rightSideList[k]->setChecked(false);
                       rightSideList[k]->setCheckable(false);
                   }
                   k++;
                }
            }

            for (int i = 0; i < 9; i++) buf[i] = 0;
            buf[1] = 0x0A;//KB State
            kbDevice.sendData(buf,9);
        }
    }

}

void MainWindow::keyClicked() {
    QMenu menu;
    QMenu key("Key",&menu);
    QMenu mod("Modifier", &menu);
    menu.addMenu(&key);
    menu.addMenu(&mod);
    QList<QMenu*> cats;
    for (int i = 0; i < keyCat.count(); i++) {
        cats.append(new QMenu(keyCat[i].name, &key));
        key.addMenu(cats[i]);
        for (int j = 0; j < keyCat[i].indexes.count(); j++) {
            QVariant v;
            QAction *a = cats[i]->addAction(keyNames[keyCat[i].indexes.at(j)]);
            v = keyCat[i].indexes.at(j);
            a->setData(v);
        }
    }
    QVariant v;
    QAction *a = mod.addAction("Clear");
    v = 0x10000; a->setData(v);
    a = mod.addAction("LCTRL");
    v = 0x0100; a->setData(v);
    a = mod.addAction("LSHIFT");
    v = 0x0200; a->setData(v);
    a = mod.addAction("LALT");
    v = 0x0400; a->setData(v);
    a = mod.addAction("LGUI");
    v = 0x0800; a->setData(v);

    a = mod.addAction("RCTRL");
    v = 0x1000; a->setData(v);
    a = mod.addAction("RSHIFT");
    v = 0x2000; a->setData(v);
    a = mod.addAction("RALT");
    v = 0x4000; a->setData(v);
    a = mod.addAction("RGUI");
    v = 0x8000; a->setData(v);

    a = mod.addAction("+LCTRL");
    v = 0x10100; a->setData(v);
    a = mod.addAction("+LSHIFT");
    v = 0x10200; a->setData(v);
    a = mod.addAction("+LALT");
    v = 0x10400; a->setData(v);
    a = mod.addAction("+LGUI");
    v = 0x10800; a->setData(v);

    a = mod.addAction("+RCTRL");
    v = 0x11000; a->setData(v);
    a = mod.addAction("+RSHIFT");
    v = 0x12000; a->setData(v);
    a = mod.addAction("+RALT");
    v = 0x14000; a->setData(v);
    a = mod.addAction("+RGUI");
    v = 0x18000; a->setData(v);
    QAction *res = menu.exec(QCursor::pos());
    if (res) {
        int val = res->data().toInt();
        QPushButton *bt = (QPushButton *)QObject::sender();
        int index = rightSideList.indexOf(bt);
        if (index >= 0) {
            if (val >= 0x10000) {
                if (val == 0x10000) rightKeymap[ui->comboBox->currentIndex()*2+1][index] = 0;
                else {
                    val = (val & 0xFFFF)>>8;
                    rightKeymap[ui->comboBox->currentIndex()*2+1][index] |= val;
                }
            }
            else if (val >= 0x100) {
                val = val>>8;
                rightKeymap[ui->comboBox->currentIndex()*2+1][index] = val;
            }
            else {
                rightKeymap[ui->comboBox->currentIndex()*2][index] = val;
            }
            rightSideList[index]->setText(keyText(index));
            keysToUpdateRight.append(index);
            if (!updateKeyTimer.isActive()) updateKeyTimer.start(100);
        }
        else {
            int index = leftSideList.indexOf(bt);
            if (index >= 0) {
                if (val >=0x10000) {
                    if (val ==0x10000) leftKeymap[ui->comboBox->currentIndex()*2+1][index] = 0;
                    else {
                        val = (val & 0xFFFF)>>8;
                        leftKeymap[ui->comboBox->currentIndex()*2+1][index] |= val;
                    }
                }
                else if (val >= 0x100) {
                    val = val>>8;
                    leftKeymap[ui->comboBox->currentIndex()*2+1][index] = val;
                }
                else {
                    leftKeymap[ui->comboBox->currentIndex()*2][index] = val;
                }
                leftSideList[index]->setText(keyText(index));
                keysToUpdateLeft.append(index);
            }
        }
    }
    for(int i = 0; i < cats.count(); i++) {
        cats[i]->clear();
        delete cats[i];
    }
    menu.clear();
}

void MainWindow::on_setCPIButton_clicked() {
    unsigned char buf[32];
    for (int i = 0; i < 9; i++) buf[i] = 0;
    buf[1] = 0x01;//Sensor resolution
    buf[2] = ui->cpiValueBox->currentIndex()+1;//
    kbDevice.sendData(buf,9);
}

void MainWindow::on_normalModeButton_clicked() {
    unsigned char buf[32];
    for (int i = 0; i < 9; i++) buf[i] = 0;
    buf[1] = 0x06;//Sensor work type
    buf[2] = 0;//
    kbDevice.sendData(buf,9);
}

void MainWindow::on_wheelModeButton_clicked() {
    unsigned char buf[32];
    for (int i = 0; i < 9; i++) buf[i] = 0;
    buf[1] = 0x06;//Sensor work type
    buf[2] = 1;//
    kbDevice.sendData(buf,9);
}

void MainWindow::on_readKeysetButton_clicked() {
    delayReadKeyPos = 0;
    delayReadKeyMap = 0;
    delayReadKeySet = 0;
    unsigned char buf[32];
    for (int i = 0; i < 9; i++) buf[i] = 0;
    buf[1] = 0x02;//Read EEPROM
    buf[2] = delayReadKeySet;//Read EEPROM
    kbDevice.sendData(buf,9);
    if (!readKeyTimer.isActive()) readKeyTimer.start(20);
    ui->progressBar->setValue(0);
}

void MainWindow::on_readStatusButton_clicked() {
    readState();
}

void MainWindow::on_comboBox_currentIndexChanged(int index) {
    for (int i = 0; i < 40; i++) {
        rightSideList[i]->setText(keyText(i));
    }
}

QString MainWindow::keyModText(int index) {
    QString str = "";
    int set = ui->comboBox->currentIndex()*2 + 1;
    if (rightKeymap[set][index] & 0x01) str += "LCTRL+";
    if (rightKeymap[set][index] & 0x02) str += "LSHIFT+";
    if (rightKeymap[set][index] & 0x04) str += "LALT+";
    if (rightKeymap[set][index] & 0x08) str += "LGUI+";
    if (rightKeymap[set][index] & 0x10) str += "RCTRL+";
    if (rightKeymap[set][index] & 0x20) str += "RSHIFT+";
    if (rightKeymap[set][index] & 0x40) str += "RALT+";
    if (rightKeymap[set][index] & 0x80) str += "RGUI+";
    if (str.length() > 0) str += "\n";
    return str;
}

QString MainWindow::keyText(int index) {
    return keyModText(index)+keyNames[rightKeymap[ui->comboBox->currentIndex()*2][index]];
}

void MainWindow::on_autoReadStateBtn_clicked()
{
    unsigned char buf[32];
    for (int i = 0; i < 9; i++) buf[i] = 0;
    buf[1] = 0x0A;//Read EEPROM
    kbDevice.sendData(buf,9);
    if (!updateStateTimer.isActive()) updateStateTimer.start(50);
    else {
        updateStateTimer.stop();
        for(int i = 0; i < rightSideList.count(); i++) {
            rightSideList[i]->setChecked(false);
            rightSideList[i]->setCheckable(false);
        }
    }
}
