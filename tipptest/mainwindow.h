#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QKeyEvent>
#include <QLabel>
#include <QPushButton>
#include <random>

#include "countdown.h"
#include "character.h"


using namespace std;

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

    int position;
    int errorCount;

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    QLabel *keyLabel;
    QLabel *textTodo;
    QPushButton *refreshButton;
    Countdown *countdown;

    vector<Character*> actualText;
    vector<Character*> generateText();
    void setTextTodo(vector<Character*> text);
    int getRandomNumber(int i);
    bool timeRunning;
    int time;


private slots:
    void refreshAll();


protected:
    void keyPressEvent(QKeyEvent *event) override; // Überschreiben der Methode

};
#endif // MAINWINDOW_H
