#include "keycategoryset.h"
#include <QString>
#include "hidkeys.h"

KeyCategorySet::KeyCategorySet()
{
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
}

QList<keyCategories> KeyCategorySet::keyCategory()
{
    return keyCat;
}

QString KeyCategorySet::keyName(int keyClass, int index)
{
    return keyNames[keyCat[keyClass].indexes.at(index)];
}

QString keyName(int index) {
    return keyNames[index];
}
