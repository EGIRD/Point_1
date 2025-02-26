#ifndef HEXAGON_H
#define HEXAGON_H

#include "regularpolygon.h"

class Hexagon : public RegularPolygon {
public:
    Hexagon(const QPoint &center, int radius, const QColor &color);
    double area() const override;
    double perimeter() const override;
    QPoint centerOfMass() const override;
    void move(int dx, int dy) override;
};

#endif // HEXAGON_H
