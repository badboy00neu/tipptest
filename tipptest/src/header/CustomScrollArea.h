//
// Created by Justus Günther on 05.04.25.
//

#ifndef TIPPTEST_CUSTOMSCROLLAREA_H
#define TIPPTEST_CUSTOMSCROLLAREA_H


#include <QScrollArea>
#include <QWheelEvent>

// A Scroll Area with disabled scrolling by mouse wheel
class CustomScrollArea : public QScrollArea {
public:
    CustomScrollArea(QWidget *parent = nullptr);

protected:
    void wheelEvent(QWheelEvent *event) override;
};


#endif //TIPPTEST_CUSTOMSCROLLAREA_H
