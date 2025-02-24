#ifndef RECTANGLE_H
#define RECTANGLE_H

#include "quadrilateral.h"

class Rectangle : public Quadrilateral {
public:
    Rectangle(const QPoint &topLeft, const QPoint &bottomRight, const QColor &color);
    double area() const override;
    double perimeter() const override;
    QPoint centerOfMass() const override;
};

#endif // RECTANGLE_H
