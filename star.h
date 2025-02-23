#ifndef STAR_H
#define STAR_H

#include "polygon.h"

class Star : public Polygon {
public:
    Star(const QPoint &center, int outerRadius, int innerRadius, int numPoints, const QColor &color);
    void draw(QPainter &painter) override; // Переопределение отрисовки

private:
    QPoint center; // Центр звезды
    int outerRadius; // Внешний радиус
    int innerRadius; // Внутренний радиус
    int numPoints; // Количество лучей
};

#endif // STAR_H
