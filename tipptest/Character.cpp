#include "Character.h"


Character::Character() {}

Character::Character(QChar value){
    this->value = value;
    this->state = untouched;
}

Character *Character::createNewSpace(){
    Character *space = new Character(' ');
    return space;
}

Character::State Character::getState(){
    return state;
}

QChar Character::getValue(){
    return value;
}

QString Character::print(bool isCurrent){
    if (isCurrent == true){
        return QString::fromStdString("<b style='color: silver;'>") + value + QString::fromStdString("</b>");
    };

    if(state == correct){
        return QString::fromStdString("<span style='color: green;'>") + value + QString::fromStdString("</span>");
    } else if (state == incorrect){
        return QString::fromStdString("<span style='color: red;'>") + value + QString::fromStdString("</span>");
    } else {
        return value;
    }
}

void Character::setState(Character::State state){
    this->state = state;
}


