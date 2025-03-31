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
    textTodo->setGeometry(350, 100, 500, 400);
    textTodo->setStyleSheet("font-size:24px;");

    time = 60;   //Zeit in s
    countdown = new Countdown(time, this);
    countdown->setGeometry(50, 50, 200, 50);


    QFont font("Monospace");
    font.setStyleHint(QFont::Monospace);
    textTodo->setFont(font);

    refreshButton = new QPushButton("Restart", this);
    refreshButton->setFocusPolicy(Qt::NoFocus);
    refreshButton->setGeometry(50, 20, 100, 30);

    connect(refreshButton, &QPushButton::clicked, this, &MainWindow::refreshAll);

    connect(countdown, &Countdown::countdownFinished, this, [this]() {
        this->position = this->actualText.size() + 1;
        keyLabel->setText("STOP");
        timeRunning = false;
        countdown->hide();
    });


    refreshAll();
}


MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::keyPressEvent(QKeyEvent *event) {
    if (actualText.size() <= position){
        keyLabel->setText("STOP");
        return;
    }
    if (!event->text().isEmpty()) {
        QChar key = event->text().at(0);
        Character *actualChar = actualText.at(position);
        if (key == ''){
            if (position > 0){
                position--;
            }
            actualChar = actualText.at(position);
            actualChar->setState(Character::untouched);
        } else if (!key.isLetterOrNumber() && key != ' '){
            qDebug() << "skipped";
            return;
        } else {
            if (timeRunning == false){
                keyLabel->setText("");
                countdown->startCountdown();
                timeRunning = true;
            }
            if(key == actualChar->getValue()){
                actualChar->setState(Character::correct);
            } else {
                actualChar->setState(Character::incorrect);
                errorCount++;
            }
            position++;
        }

        setTextTodo(actualText);

        if (actualText.size() <= position){
            keyLabel->setText("ENDE");
        }
    }
}

void MainWindow::refreshAll(){
    timeRunning = false;
    countdown->setRemainingTime(time);
    countdown->hide();

    keyLabel->setText("Press a key to start");
    position = 0;
    actualText = generateText();
    setTextTodo(actualText);
}

void MainWindow::setTextTodo(vector<Character*> text){
    QString builder = "";
    for (int i = 0; i < text.size(); i++){
        builder.append(text.at(i)->print(i == position));
    }
    textTodo->setText(builder);
}


vector<Character*> MainWindow::generateText(){
    vector<Character*> out = {};
    vector<string> words = {
        "cat", "dog", "house", "tree", "car", "book", "phone", "chair", "table", "window",
        "door", "cup", "water", "food", "garden", "school", "teacher", "student", "friend", "family",
        "city", "country", "river", "mountain", "ocean", "forest", "computer", "keyboard", "mouse", "bottle",
        "run", "jump", "walk", "eat", "sleep", "read", "write", "play", "sing", "dance",
        "love", "happiness", "anger", "time", "day", "night", "light", "dark", "song", "music",
        "flower", "cloud", "rain", "sun", "moon", "star", "road", "bridge", "game", "story",
        "child", "adult", "parent", "room", "floor", "bed", "pillow", "wall", "picture", "clock",
        "hat", "shirt", "pants", "shoes", "bag", "box", "pen", "paper", "idea", "dream"
    };



    for (int i = 0; i < 500; i++){
        string randomWord = words.at(getRandomNumber(words.size()-1));
        for (int j = 0; j < randomWord.size(); j++){
            out.push_back(new Character(randomWord.at(j)));
        }
        out.push_back(Character::createNewSpace());
    }
    return out;
}

int MainWindow::getRandomNumber(int i) {
    std::random_device rd;
    std::mt19937 generator(rd());
    std::uniform_int_distribution<> distribution(0, i);

    return distribution(generator);
}






