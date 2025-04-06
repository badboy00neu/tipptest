#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QKeyEvent>
#include <QLabel>
#include <QPushButton>
#include <random>
#include <QScrollArea>
# include <QScrollBar>

#include "countdown.h"
#include "character.h"
#include "CustomScrollArea.h"


using namespace std;

QT_BEGIN_NAMESPACE
namespace Ui {
    class MainWindow;
}
QT_END_NAMESPACE

// handles the user input, ui and process flow
class MainWindow : public QMainWindow {
Q_OBJECT

    int position;       //current Position
    int errorCount;     // Total mistakes made during Test
    int currentLine;

public:
    MainWindow(QWidget *parent = nullptr);

    ~MainWindow();

private:
    Ui::MainWindow *ui;
    QLabel *infoLabel;
    QLabel *textTodo;
    QLabel *resultLabel;
    QPushButton *refreshButton;
    QPushButton *time10;
    QPushButton *time30;
    QPushButton *time60;
    QPushButton *time180;
    CustomScrollArea *scrollArea;
    QMap<int, QPushButton *> buttons;

    bool testRunning;
    bool testEnd;
    int time;
    int lineCount;
    int lastLineLength;
    Countdown *countdown;
    vector<Character *> actualText;

    vector<Character *> generateText(int count);

    void setTextTodo(vector<Character *> text);

    static int getRandomNumber(int i);

    void setTimeButtonsStyleToDefault();

    void setTimeButtonsDisabled(bool disable);

    void selectTime(QPushButton *button);

    void selectButton(int time);

    void startTest();

    QString countCharErrorsAndSuccess();

    void scrollToLine(int lineIndex);

private slots:

    void refreshAll();

    void endTest();

protected:
    void keyPressEvent(QKeyEvent *event) override; // Überschreiben der Methode

};

#endif // MAINWINDOW_H
