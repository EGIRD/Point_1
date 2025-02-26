#ifndef POLYGON_H
#define POLYGON_H

#include "shape.h"
#include <QVector>
#include <QPoint>

class Polygon : public Shape {
public:
    Polygon(const QColor &color);
    void addPoint(const QPoint &point); // Добавление точки
    void draw(QPainter &painter) override; // Отрисовка полигона
     bool contains(const QPoint &point) const override;
    // QRect boundingRect() const override;

protected:
    QVector<QPoint> points; // Вектор точек
};

#endif // POLYGON_H
