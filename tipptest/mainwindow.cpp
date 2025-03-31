#include "mainwindow.h"
#include "ui_mainwindow.h"

using namespace std;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setFixedSize(1200, 600);

    keyLabel = new QLabel("Press a key to start", this);
    keyLabel->setAlignment(Qt::AlignCenter);
    keyLabel->setGeometry(50, 50, 200, 50);
    keyLabel->setStyleSheet("font-size: 18px; border: 1px solid black; padding: 5px;");

    textTodo = new QLabel("", this);
    textTodo->setAlignment(Qt::AlignLeft);
    textTodo->setWordWrap(true);
    textTodo->setGeometry(350, 150, 500, 50);

    words = getWords();
    text="";
    for (int i = 0; i < words.size(); i++){

        text.append(' ' + (words.at(i))->printName());
    }
    text = text.trimmed();
    textTodo->setText(text);

    position = 0;
    currentWord = words.at(position);
    wordIndex = 0;
}


MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::keyPressEvent(QKeyEvent *event) {
    if (text.size() <= position){
        keyLabel->setText("ENDE");
        return;
    }
    if (!event->text().isEmpty()) {
        QChar key = event->text().at(0);

        if (key == ''){
            keyLabel->setText(QString("zurück"));
            position--;
            textTodo->setText(greenText(text, position));

        } else if ((key == ' ' && text.endsWith(' ')) || (!key.isLetterOrNumber() && key != ' ')){
            qDebug() << "skipped";
            return;
        } else {
            qDebug() << key + QString::fromStdString("<>") + text.at(position);
            if(key == text.at(position)){
                keyLabel->setText(QString("richtig"));
                position++;
                textTodo->setText(greenText(text, position));
            } else{
                keyLabel->setText(QString("falsch"));
                errorCount++;
            }
        }
        if (text.size() <= position){
            keyLabel->setText("ENDE");
        }
    }
}

QString MainWindow::greenText(QString in, int position){
    QString out = QString::fromStdString("<span style='color:green;'>");
    out.append(in.first(position));
    out.append("</span>");
    qDebug() << in.size()-position;
    out.append(in.last(in.size()-position));
    return out;
}

void MainWindow::nextWord(){
    position++;
    currentWord = words.at(position);
}



vector<word*> MainWindow::getWords(){
    return createWords({"Apple", "Banana", "Cherry", "Date", "Elderberry"});
}

vector<word*> MainWindow::createWords(vector<string> words){
    vector<word*> out = {};
    for (int i = 0; i < words.size(); i++){
        out.push_back(new word(QString::fromStdString(words.at(i))));
    }
    return out;
}


