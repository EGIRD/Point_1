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
     void move(int dx, int dy) override;
};

#endif // SQUARE_H
