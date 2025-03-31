#include "character.h"


character::character() {}

character::character(QChar value){
    this->value = value;
}

character::State character::getState(){
    return state;
}

QChar character::getValue(){
    return value;
}

QString character::printValue(){
    if (state == untouched){
        return value;
    }
}

void character::setState(character::State state){
    this->state = state;
}



