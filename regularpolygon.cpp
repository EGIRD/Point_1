#include "regularpolygon.h"
#include <cmath>

RegularPolygon::RegularPolygon(const QPoint &center, int radius, int numSides, const QColor &color)
    : Polygon(color), center(center), radius(radius), numSides(numSides) {
    double angleIncrement = 2 * M_PI / numSides;
    for (int i = 0; i < numSides; ++i) {
        double angle = i * angleIncrement;
        int x = center.x() + radius * cos(angle);
        int y = center.y() + radius * sin(angle);
        addPoint(QPoint(x, y));
    }
}

void RegularPolygon::draw(QPainter &painter) {
    painter.setPen(color);
    painter.drawPolygon(points.data(), points.size());
}
