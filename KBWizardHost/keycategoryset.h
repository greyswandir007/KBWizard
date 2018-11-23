#ifndef KEYCATEGORYSET_H
#define KEYCATEGORYSET_H

#include <QList>
#include <QString>


struct keyCategories {
    QString name;
    QList<int> indexes;
};


class KeyCategorySet
{
public:
    KeyCategorySet();
    QList<keyCategories> keyCategory();
    QString keyName(int keyClass, int index);
    QString keyName(int index);

private:
    QList<keyCategories> keyCat;
};

#endif // KEYCATEGORYSET_H
