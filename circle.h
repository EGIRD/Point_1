#ifndef CIRCLE_H
#define CIRCLE_H

#include "shape.h"
#include <QPoint>
#include <QColor>

class Circle : public Shape {
public:
    Circle(const QPoint &center, int radius, const QColor &color);
    void draw(QPainter &painter) override;

private:
    QPoint center; // Центр круга
    int radius; // Радиус круга
};

#endif // CIRCLE_H
