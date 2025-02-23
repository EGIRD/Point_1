#ifndef CIRCLE_H
#define CIRCLE_H

#include "shape.h"

class Circle : public Shape {
public:
    Circle(const QPoint &center, int radius, const QColor &color);
    void draw(QPainter &painter) override;
private:
    QPoint center;
    int radius;
};

#endif // CIRCLE_H
