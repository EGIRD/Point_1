#ifndef TRIANGLE_H
#define TRIANGLE_H

#include "polygon.h"

class Triangle : public Polygon {
public:
    Triangle(const QPoint &p1, const QPoint &p2, const QPoint &p3, const QColor &color);
    void draw(QPainter &painter) override;
    double area() const override;
    double perimeter() const override;
    QPoint centerOfMass() const override;
    bool contains(const QPoint &point) const override;
    void move(int dx, int dy) override;
    void scale(double factor) override;

};

#endif // TRIANGLE_H
