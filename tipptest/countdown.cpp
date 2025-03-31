#include "Countdown.h"

Countdown::Countdown(int seconds, QWidget *parent)
    : QLCDNumber(parent), remainingTime(seconds) {
    setSegmentStyle(Filled);
    display(remainingTime);

    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &Countdown::updateCountdown);
    hide();
}

void Countdown::startCountdown() {
    show();
    timer->start(1000);
}

void Countdown::stopCountdown() {
    hide();
    timer->stop();
}

void Countdown::updateCountdown() {
    if (remainingTime > 0) {
        remainingTime--;
        display(remainingTime);
    } else {
        stopCountdown();
        emit countdownFinished();
    }
}

void Countdown::setRemainingTime(int time){
    stopCountdown();
    remainingTime = time;
    display(remainingTime);
}
