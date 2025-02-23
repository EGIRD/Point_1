#include "quadrilateral.h"

Quadrilateral::Quadrilateral(const QColor &color) : Polygon(color) {}

void Quadrilateral::draw(QPainter &painter) {
    painter.setPen(color);
    painter.drawPolygon(points.data(), points.size());
}
