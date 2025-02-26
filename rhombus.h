#ifndef RHOMBUS_H
#define RHOMBUS_H

#include "polygon.h"

class Rhombus : public Polygon {
public:
    Rhombus(const QPoint &center, int width, int height, const QColor &color);
    void draw(QPainter &painter) override;
    double area() const override;
    double perimeter() const override;
    QPoint centerOfMass() const override;
    bool contains(const QPoint &point) const override;
    void move(int dx, int dy) override;
};

#endif // RHOMBUS_H
