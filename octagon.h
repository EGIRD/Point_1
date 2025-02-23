#ifndef OCTAGON_H
#define OCTAGON_H

#include "regularpolygon.h"

class Octagon : public RegularPolygon {
public:
    Octagon(const QPoint &center, int radius, const QColor &color);
    void draw(QPainter &painter) override;
};

#endif // OCTAGON_H
