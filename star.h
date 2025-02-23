#ifndef STAR_H
#define STAR_H

#include "polygon.h"

class Star : public Polygon {
public:
    Star(const QPoint &center, int outerRadius, int innerRadius, int numPoints, const QColor &color);
    void draw(QPainter &painter) override;

private:
    QPoint center;
    int outerRadius;
    int innerRadius;
    int numPoints;
};

#endif // STAR_H
