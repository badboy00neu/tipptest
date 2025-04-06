#ifndef COUNTDOWN_H
#define COUNTDOWN_H

#include <QLCDNumber>
#include <QTimer>

// a countdown that displays the remaining time and emits a signal on finish
class Countdown : public QLCDNumber {
Q_OBJECT

public:
    explicit Countdown(int seconds, QWidget *parent = nullptr);

    void startCountdown();

    void stopCountdown();

    void setRemainingTime(int time);

signals:

    void countdownFinished();

private slots:

    void updateCountdown();

private:
    int remainingTime;
    QTimer *timer;

    QString formatTime(int remainingTime);
};

#endif // COUNTDOWN_H
