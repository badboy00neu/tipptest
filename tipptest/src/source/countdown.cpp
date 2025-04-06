#include "../header/countdown.h"

Countdown::Countdown(int seconds, QWidget *parent)
        : QLCDNumber(parent), remainingTime(seconds) {
    setSegmentStyle(Filled);
    display(formatTime(remainingTime));

    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &Countdown::updateCountdown);
    hide();
}

void Countdown::startCountdown() {
    timer->stop();
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
        display(formatTime(remainingTime));
    } else {
        stopCountdown();
        emit countdownFinished();
    }
}

void Countdown::setRemainingTime(int time) {
    stopCountdown();
    remainingTime = time;
    display(formatTime(remainingTime));
}

QString Countdown::formatTime(int remainingTime) {
    int minutes = remainingTime / 60;
    int seconds = remainingTime % 60;
    return QString("%1:%2")
            .arg(minutes, 2, 10, QLatin1Char('0'))
            .arg(seconds, 2, 10, QLatin1Char('0'));
}

