#ifndef SQUARE_H
#define SQUARE_H

#include "rectangle.h"

class Square : public Rectangle {
public:
    Square(const QPoint &center, int sideLength, const QColor &color);
    double area() const override;
    double perimeter() const override;
    QPoint centerOfMass() const override;
    bool contains(const QPoint &point) const override;
    // QRect boundingRect() const override;
};

#endif // SQUARE_H
