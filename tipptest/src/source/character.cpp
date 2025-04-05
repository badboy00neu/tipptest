#include "../header/character.h"


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
    if (isCurrent){
        return QString::fromStdString("<b style='color: silver;'>") + value + QString::fromStdString("</b>");
    };


    if(state == correct){
        return QString::fromStdString("<span style='color: green;'>") + value + QString::fromStdString("</span>");
    } else if (state == incorrect){
        if (value == ' '){
            return QString::fromStdString("<span style='background: red;'>") + value + QString::fromStdString("</span>");
        } else {
            return QString::fromStdString("<span style='color: red;'>") + value + QString::fromStdString("</span>");
        }
    } else {
        return value;
    }
}

void Character::setState(Character::State state){
    this->state = state;
}


