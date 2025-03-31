#ifndef WORD_H
#define WORD_H

#include <QString>
#include "character.h"
using namespace std;

class word
{
    vector<character*> name;
    int count;
    int lastPosition;

public:
    word(QString name);
    vector<character*> getName();
    QString printName();
};

#endif // WORD_H
