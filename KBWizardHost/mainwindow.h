#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>
#include <QList>
#include <QPushButton>

#include "kbwizardhid.h"

namespace Ui {
class MainWindow;
}

struct keyCategories {
    QString name;
    QList<int> indexes;
};

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void readState();

private slots:
    void timedEvent();
    void readKeysetEvent();
    void updateKeysetEvent();
    void updateStateEvent();
    void keyClicked();
    void on_openButton_clicked();
    void on_closeButton_clicked();
    void on_readButton_clicked();
    void on_autoReadButton_clicked();
    void on_setCPIButton_clicked();
    void on_normalModeButton_clicked();
    void on_wheelModeButton_clicked();
    void on_readKeysetButton_clicked();
    void on_readStatusButton_clicked();
    void on_comboBox_currentIndexChanged(int index);
    void on_autoReadStateBtn_clicked();

private:
    QString keyModText(int index);
    QString keyText(int index);
    Ui::MainWindow *ui;
    KBWizardHID kbDevice;
    QTimer timer1, readKeyTimer, updateKeyTimer, updateStateTimer;
    int minx, maxx;
    int miny, maxy;
    bool firstRead;
    int delayReadKeyPos;
    int delayReadKeyMap;
    int delayReadKeySet;

    QList<QPushButton*> rightSideList;
    QList<QPushButton*> leftSideList;
    uint8_t  rightKeymap[4][40]; // keyMap
    uint8_t  leftKeymap[4][40]; // keyMap
    uint32_t rightKeyStat[40];
    uint32_t leftKeyStat[40];
    QList<keyCategories> keyCat;
    QList<int> keysToUpdateLeft;
    QList<int> keysToUpdateRight;
};

#endif // MAINWINDOW_H
