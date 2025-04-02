#ifndef Character_H
#define Character_H

#include <QChar>
#include <QString>


class Character
{

public:
    enum State {
        untouched,
        correct,
        incorrect,
    };

    Character();
    Character(QChar value);
    static Character *createNewSpace();
    State getState();
    void setState(State state);
    QChar getValue();
    QString print(bool isBold);


private:
    QChar value;
    State state = untouched;
};

#endif // Character_H
