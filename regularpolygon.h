#ifndef REGULARPOLYGON_H
#define REGULARPOLYGON_H

#include "polygon.h"

class RegularPolygon : public Polygon {
public:
    RegularPolygon(const QPoint &center, int radius, int numSides, const QColor &color);
    void draw(QPainter &painter) override;

protected:
    QPoint center;
    int radius;
    int numSides;
};

#endif // REGULARPOLYGON_H
