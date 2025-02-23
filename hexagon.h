#ifndef HEXAGON_H
#define HEXAGON_H

#include "regularpolygon.h"

class Hexagon : public RegularPolygon {
public:
    Hexagon(const QPoint &center, int radius, const QColor &color);
    void draw(QPainter &painter) override;
};

#endif // HEXAGON_H
