#ifndef SQUARE_H
#define SQUARE_H

#include "rectangle.h"

class Square : public Rectangle {
public:
    Square(const QPoint &topLeft, int sideLength, const QColor &color);
    void draw(QPainter &painter) override;
};

#endif // SQUARE_H
