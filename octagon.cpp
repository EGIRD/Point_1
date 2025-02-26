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

void Octagon::move(int dx, int dy) {
    center.setX(center.x() + dx);
    center.setY(center.y() + dy);
    points.clear(); // Очищаем точки
    double angleIncrement = 2 * M_PI / numSides;
    for (int i = 0; i < numSides; ++i) {
        double angle = i * angleIncrement;
        int x = center.x() + radius * cos(angle);
        int y = center.y() + radius * sin(angle);
        addPoint(QPoint(x, y));
    }
}
