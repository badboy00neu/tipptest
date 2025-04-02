#include "countdown.h"

Countdown::Countdown(int seconds, QWidget *parent)
    : QLCDNumber(parent), remainingTime(seconds) {
    setSegmentStyle(Filled);
    display(formatTime(remainingTime));

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
        display(formatTime(remainingTime));
    } else {
        stopCountdown();
        emit countdownFinished();
    }
}

void Countdown::setRemainingTime(int time){
    stopCountdown();
    remainingTime = time;
    display(formatTime(remainingTime));
}

QString Countdown::formatTime(int remainingTime){
    std::string mm = std::to_string(remainingTime / 60);
    std::string ss = std::to_string(remainingTime % 60);
    if (mm.size()<2){
        mm.insert(0, "0");
    }
    if (ss.size()<2){
        ss.insert(0, "0");
    }

    return QString::fromStdString(mm) + ":" + QString::fromStdString(ss);
}

