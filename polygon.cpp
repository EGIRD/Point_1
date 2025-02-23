#include "polygon.h"

Polygon::Polygon(const QColor &color) : Shape(color) {}

void Polygon::addPoint(const QPoint &point) {
    points.append(point);
}

void Polygon::draw(QPainter &painter) {
    if (points.size() > 1) {
        painter.setPen(color);
        painter.drawPolygon(points.data(), points.size());
    }
}
