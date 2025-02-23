#ifndef TRIANGLE_H
#define TRIANGLE_H

#include "polygon.h"

class Triangle : public Polygon {
public:
    Triangle(const QPoint &p1, const QPoint &p2, const QPoint &p3, const QColor &color);
    void draw(QPainter &painter) override; // Переопределение отрисовки
};

#endif // TRIANGLE_H
