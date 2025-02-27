#ifndef OCTAGON_H
#define OCTAGON_H

#include "regularpolygon.h"

class Octagon : public RegularPolygon {
public:
    Octagon(const QPoint &center, int radius, const QColor &color);
    double area() const override;
    double perimeter() const override;
    QPoint centerOfMass() const override;
    void move(int dx, int dy) override;
    void scale(double factor) override;
};

#endif // OCTAGON_H
