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
    bool isFirstInLine();
    void setFirst(bool isFirst);


private:
    QChar value;
    State state = untouched;
    bool first;
};

#endif // Character_H
