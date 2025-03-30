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
}


MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::keyPressEvent(QKeyEvent *event) {
    if (!event->text().isEmpty()) {
        QChar key = event->text().at(0);
        QString currentText = textTodo->text();

        if (key == ''){
            textTodo->setText(textTodo->text().removeLast());

        } else if ((key == ' ' && currentText.endsWith(' ')) || (!key.isLetterOrNumber() && key != ' ')){
            qDebug() << "skipped";
            return;
        } else {
            keyLabel->setText(QString("Last key: ") + key);
            textTodo->setText(currentText + key);

        }
        qDebug() << "Latest key pressed: " << key;
    }
}

vector<string> getWords(){
    return {"Apple", "Banana", "Cherry", "Date", "Elderberry"};
}


