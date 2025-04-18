#include "../header/mainwindow.h"

using namespace std;

MainWindow::MainWindow(QWidget *parent)
        : QMainWindow(parent) {

    // set Styles
    setFixedSize(1200, 600);

    infoLabel = new QLabel("Press a key to start", this);
    infoLabel->setAlignment(Qt::AlignCenter);
    infoLabel->setGeometry(50, 50, 200, 50);
    infoLabel->setStyleSheet("font-size: 18px; border: 1px solid black; padding: 5px;");

    resultLabel = new QLabel("", this);
    resultLabel->setAlignment(Qt::AlignTop);
    resultLabel->setGeometry(50, 175, 200, 200);
    resultLabel->setStyleSheet("font-size: 18px;");

    // main text
    scrollArea = new CustomScrollArea(this);
    textTodo = new QLabel(scrollArea);

    scrollArea->setStyleSheet("padding:5px; padding-top: 20px; padding-bottom: 20px;");
    scrollArea->setGeometry(350, 100, 500, 400);
    scrollArea->setWidget(textTodo);
    scrollArea->setWidgetResizable(true);
    scrollArea->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    scrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    QFont font("Menlo");
    font.setStyleHint(QFont::Monospace);
    textTodo->setFont(font);
    textTodo->setAlignment(Qt::AlignLeft);
    textTodo->setWordWrap(true);
    textTodo->setStyleSheet("font-size:24px;");
    textTodo->setWordWrap(false);

    time = 60; //Default duration
    countdown = new Countdown(time, this);
    countdown->setGeometry(50, 50, 200, 50);

    // time-select buttons
    time10 = new QPushButton("10s", this);
    time10->setGeometry(50, 100, 95, 30);
    time10->setFocusPolicy(Qt::NoFocus);
    buttons.insert(10, time10);

    time30 = new QPushButton("30s", this);
    time30->setGeometry(155, 100, 95, 30);
    time30->setFocusPolicy(Qt::NoFocus);
    buttons.insert(30, time30);

    time60 = new QPushButton("1min", this);
    time60->setGeometry(50, 130, 95, 30);
    time60->setFocusPolicy(Qt::NoFocus);
    buttons.insert(60, time60);

    time180 = new QPushButton("3min", this);
    time180->setGeometry(155, 130, 95, 30);
    time180->setFocusPolicy(Qt::NoFocus);
    buttons.insert(180, time180);

    restartButton = new QPushButton("Restart", this);
    restartButton->setFocusPolicy(Qt::NoFocus);
    restartButton->setGeometry(50, 20, 100, 30);

    connect(restartButton, &QPushButton::clicked, this, &MainWindow::refreshAll);

    connect(time10, &QPushButton::clicked, this, [this]() {
        selectTime(time10);
    });
    connect(time30, &QPushButton::clicked, this, [this]() {
        selectTime(time30);
    });
    connect(time60, &QPushButton::clicked, this, [this]() {
        selectTime(time60);
    });
    connect(time180, &QPushButton::clicked, this, [this]() {
        selectTime(time180);
    });

    connect(countdown, &Countdown::countdownFinished, this, &MainWindow::endTest);

    refreshAll();
}


MainWindow::~MainWindow() {
    for (Character *c: actualText) {
        delete c;
    }
    actualText.clear();
}

// handles users keyboard input
void MainWindow::keyPressEvent(QKeyEvent *event) {
    if (testEnd) {  //waiting for refresh
        return;
    }
    if (!event->text().isEmpty()) {         // ignore empty input
        QChar key = event->text().at(0);
        Character *actualChar = actualText.at(position);
        if (key == '') {   // delete
            if (position > 0) {
                if (actualChar->isFirstInLine()) {
                    currentLine--;
                    scrollToLine(currentLine);
                }
                position--;
            }
            actualChar = actualText.at(position);
            actualChar->setState(Character::untouched);
        } else if (!key.isLetterOrNumber() && key != ' ') { // ignore invalid input
            return;
        } else {
            if (!testRunning) {
                startTest();
            }
            if (key == actualChar->getValue()) {    // correct
                actualChar->setState(Character::correct);
            } else {                                // incorrect
                actualChar->setState(Character::incorrect);
                errorCount++;
            }
            position++;
            if (position < actualText.size() && actualText.at(position)->isFirstInLine()) { // auto-scroll to next line
                currentLine++;
                scrollToLine(currentLine);
            }
        }
        setTextTodo(actualText);

        if (currentLine + 14 >= lineCount) { // load more words in advance if necessary
            vector<Character *> moreText = generateText(80);
            actualText.insert(actualText.end(), moreText.begin(), moreText.end());
        }
    }
}

// sets elements to start a test
void MainWindow::startTest() {
    setTimeButtonsDisabled(true);
    infoLabel->setText("");
    countdown->setRemainingTime(time);
    countdown->startCountdown();
    testRunning = true;
}

// sets elements to be in the end state after a finished test
void MainWindow::endTest() {
    testEnd = true;
    infoLabel->setText("STOP");
    testRunning = false;
    countdown->hide();
    resultLabel->setText(countCharErrorsAndSuccess());
}

// resets the elements to be ready to start a test
void MainWindow::refreshAll() {
    testEnd = false;
    testRunning = false;
    countdown->setRemainingTime(time);
    countdown->hide();
    setTimeButtonsDisabled(false);
    selectButton(time);

    errorCount = 0;
    position = 0;
    currentLine = 0;
    lineCount = 0;
    lastLineLength = 0;

    scrollToLine(position);
    infoLabel->setText("Press a key to start");
    resultLabel->setText("");
    actualText = generateText(160);
    setTextTodo(actualText);
}

// sets the main text with correct style
void MainWindow::setTextTodo(vector<Character *> text) {
    QString builder = "";
    for (int i = 0; i < text.size(); i++) {
        if (text.at(i)->isFirstInLine()) {
            builder.append("<br>");
        }
        builder.append(text.at(i)->print(i == position));
    }
    textTodo->setText(builder);
}

// generates the random text as Characters
vector<Character *> MainWindow::generateText(int count) {
    vector<Character *> out = {};
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
    int currentLineLength = lastLineLength;
    for (int i = 0; i < count; i++) {
        bool overflow = false;

        const string &randomWord = words.at(getRandomNumber(words.size() - 1));
        if (currentLineLength + randomWord.size() > 32) {   // Max characters per line exceeded
            overflow = true;
            lineCount++;
            currentLineLength = 0;
        }
        for (int j = 0; j < randomWord.size(); j++) {
            Character *newChar = new Character(randomWord.at(j));
            newChar->setFirst(overflow && j == 0);
            out.push_back(newChar);
            currentLineLength++;
        }
        out.push_back(Character::createNewSpace());
        currentLineLength++;
    }
    lastLineLength = currentLineLength;
    return out;
}

// generates a random number from 0 to i
int MainWindow::getRandomNumber(int i) {
    std::random_device rd;
    std::mt19937 generator(rd());
    std::uniform_int_distribution<> distribution(0, i);
    return distribution(generator);
}

// sets the time based on the pressed button
void MainWindow::selectTime(QPushButton *button) {
    setTimeButtonsStyleToDefault();
    button->setStyleSheet("text-decoration: underline;");
    time = buttons.key(button);
}

// selects a button based on the set time
void MainWindow::selectButton(int timeToSelect) {
    setTimeButtonsStyleToDefault();
    buttons.value(timeToSelect)->setStyleSheet("text-decoration: underline;");
}

// resets the buttons style
void MainWindow::setTimeButtonsStyleToDefault() {
    for (int i = 0; i < buttons.count(); i++) {
        buttons.values().at(i)->setStyleSheet("");
    }
}

// disable = true: disables all buttons, else enables them
void MainWindow::setTimeButtonsDisabled(bool disable) {
    for (int i = 0; i < buttons.count(); i++) {
        buttons.values().at(i)->setDisabled(disable);
    }
}

// calculates the result and generates a formatted string
QString MainWindow::countCharErrorsAndSuccess() {
    int mistakeCount = 0;
    int successCount = 0;
    for (auto &i: actualText) {
        if (i->getState() == Character::incorrect) {
            mistakeCount++;
        } else if (i->getState() == Character::correct) {
            successCount++;
        }
    }
    int correctedCount = errorCount - mistakeCount;
    double totalCount = errorCount + successCount;
    int netWpm = round(((totalCount / 5.00) - (mistakeCount / 5.00)) / (time / 60.00));
    QString result = "";
    result.append("WPM: " + QString::number(netWpm) + "\n");
    result.append("Total characters: " + QString::number(totalCount) + "\n");
    result.append("False characters: " + QString::number(mistakeCount) + "\n");
    result.append("Corrected characters: " + QString::number(correctedCount));
    return result;
}

// scrolls the main text to the line of lineIndex
void MainWindow::scrollToLine(int lineIndex) {
    int lineHeight = textTodo->fontMetrics().height();
    int yOffset = lineHeight * lineIndex;
    scrollArea->verticalScrollBar()->setValue(yOffset);
}



