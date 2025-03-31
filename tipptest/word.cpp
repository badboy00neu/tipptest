#include "word.h"

word::word(QString name) {
    for (int i = 0; i<name.size(); i++){
        this->name.push_back(new character(name.at(i)));
    }
    this->count = 0;
}

QString word::printName(){
    QString out = "";
    for (int i = 0; i<name.size(); i++){
        out.append(name.at(i)->getValue());
    };
    return out;
}
