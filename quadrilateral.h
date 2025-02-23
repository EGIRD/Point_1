#ifndef QUADRILATERAL_H
#define QUADRILATERAL_H

#include "polygon.h"

class Quadrilateral : public Polygon {
public:
    Quadrilateral(const QColor &color);
    void draw(QPainter &painter) override;
};

#endif // QUADRILATERAL_H
