#ifndef CHARACTER_H
#define CHARACTER_H

#include <QChar>
#include <QString>


class character
{

public:
    enum State {
        untouched,
        correct,
        incorrect,
    };

    character();
    character(QChar value);
    State getState();
    void setState(State state);
    QChar getValue();
    QString printValue();


private:
    QChar value;
    State state = untouched;
};

#endif // CHARACTER_H
