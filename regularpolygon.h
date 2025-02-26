#ifndef REGULARPOLYGON_H
#define REGULARPOLYGON_H

#include "polygon.h"

class RegularPolygon : public Polygon {
public:
    RegularPolygon(const QPoint &center, int radius, int numSides, const QColor &color);
    double area() const override;
    double perimeter() const override;
    QPoint centerOfMass() const override;
    bool contains(const QPoint &point) const override;

protected:
    QPoint center;
    int radius;
    int numSides;
};

#endif // REGULARPOLYGON_H
