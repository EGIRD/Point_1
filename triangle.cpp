#include "triangle.h"

Triangle::Triangle(const QPoint &p1, const QPoint &p2, const QPoint &p3, const QColor &color)
    : Polygon(color) {
    addPoint(p1);
    addPoint(p2);
    addPoint(p3);
}

void Triangle::draw(QPainter &painter) {
    painter.setPen(color);
    painter.drawPolygon(points.data(), points.size());
}
