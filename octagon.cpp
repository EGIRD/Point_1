#include "octagon.h"
#include <cmath>

Octagon::Octagon(const QPoint &center, int radius, const QColor &color)
    : RegularPolygon(center, radius, 8, color) {}

double Octagon::area() const {
    return 2 * (1 + sqrt(2)) * radius * radius;
}

double Octagon::perimeter() const {
    return 8 * radius;
}

QPoint Octagon::centerOfMass() const {
    return center;
}
