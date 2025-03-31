#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QKeyEvent>
#include <QLabel>

#include "word.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT
    word* currentWord;
    int position;
    int wordIndex;
    int errorCount;

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    vector<word*> getWords();
    vector<word*> createWords(vector<string>);

private:
    Ui::MainWindow *ui;
    QLabel *keyLabel;
    QLabel *textTodo;
    void nextWord();
    vector<word*> words;
    QString greenText(QString in, int position);
    QString text;
    QString checkedChar(QString text, QString input, int position);

protected:
    void keyPressEvent(QKeyEvent *event) override; // Überschreiben der Methode

};
#endif // MAINWINDOW_H
