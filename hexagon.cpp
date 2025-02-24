#include "hexagon.h"
#include <cmath>

Hexagon::Hexagon(const QPoint &center, int radius, const QColor &color)
    : RegularPolygon(center, radius, 6, color) {}

double Hexagon::area() const {
    return (3 * sqrt(3) * radius * radius) / 2;
}

double Hexagon::perimeter() const {
    return 6 * radius;
}

QPoint Hexagon::centerOfMass() const {
    return center;
}
