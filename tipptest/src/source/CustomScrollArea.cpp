//
// Created by Justus Günther on 05.04.25.
//

#include "../header/CustomScrollArea.h"

CustomScrollArea::CustomScrollArea(QWidget *parent) : QScrollArea(parent) {}

void CustomScrollArea::wheelEvent(QWheelEvent *event) {
    event->ignore();
}

