#ifndef BUTTONSET_H
#define BUTTONSET_H

#include <QWidget>
#include <QPushButton>

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
    Q_PROPERTY(bool rightSide READ isRightSide WRITE setRightSide)

private:
    Ui::ButtonSet *ui;
    QList<QPushButton*> keyList;
    QList<QPoint> pointPos;
    int buttonSize;
    bool rightSideMap = false;
};

#endif // BUTTONSET_H
