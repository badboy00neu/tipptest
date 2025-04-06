#include "../header/mainwindow.h"


#include <QApplication>

int main(int argc, char *argv[]) {
    qDebug() << "Qt version:" << QT_VERSION_STR;
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
