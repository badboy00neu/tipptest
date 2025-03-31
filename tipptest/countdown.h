#ifndef COUNTDOWN_H
#define COUNTDOWN_H

#include <QLCDNumber>
#include <QTimer>

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
};

#endif // COUNTDOWN_H
