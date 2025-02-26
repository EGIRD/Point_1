#ifndef RECTANGLE_H
#define RECTANGLE_H

#include "quadrilateral.h"
#include <QPainter>

class Rectangle : public Quadrilateral {
public:
    Rectangle(const QPoint &topLeft, const QPoint &bottomRight, const QColor &color);
    double area() const override;
    double perimeter() const override;
    QPoint centerOfMass() const override;
    bool contains(const QPoint &point) const override;
    void move(int dx, int dy) override;
    void scale(double factor) override;


};

#endif // RECTANGLE_H
