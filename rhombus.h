#ifndef RHOMBUS_H
#define RHOMBUS_H

#include "polygon.h"

class Rhombus : public Polygon {
public:
    Rhombus(const QPoint &center, int width, int height, const QColor &color);
    void draw(QPainter &painter) override;
};

#endif // RHOMBUS_H
