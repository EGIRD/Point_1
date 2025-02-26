#ifndef CIRCLE_H
#define CIRCLE_H

#include "shape.h"
#include <QPoint>
#include <QColor>

class Circle : public Shape {
public:
    Circle(const QPoint &center, int radius, const QColor &color);
    void draw(QPainter &painter) override;
    double area() const override;
    double perimeter() const override;
    QPoint centerOfMass() const override;
     bool contains(const QPoint &point) const override;
    // QRect boundingRect() const override;
private:
    QPoint center; // Центр круга
    int radius; // Радиус круга
};

#endif // CIRCLE_H
