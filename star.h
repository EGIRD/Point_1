#ifndef STAR_H
#define STAR_H

#include "polygon.h"
#include <cmath>

class Star : public Polygon {
public:
    Star(const QPoint& center, int outerRadius, int innerRadius,
         int numPoints, double startAngle = 0.0, const QColor& color = Qt::black);

    double area() const override; // Площадь звезды
    double perimeter() const override; // Периметр звезды
    QPoint centerOfMass() const override; // Центр масс звезды
     bool contains(const QPoint &point) const override;
    // QRect boundingRect() const override;

protected:
    void calculatePoints(); // Вычисление вершин звезды

    QPoint center; // Центр звезды
    int outerRadius; // Внешний радиус
    int innerRadius; // Внутренний радиус
    int numPoints; // Количество вершин
    double startAngle; // Угол поворота
};

#endif // STAR_H
