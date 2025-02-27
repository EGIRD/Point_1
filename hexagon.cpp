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

void Hexagon::move(int dx, int dy) {
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

void Hexagon::scale(double factor) {
    radius *= factor; // Масштабируем радиус
    points.clear(); // Очищаем точки
    double angleIncrement = 2 * M_PI / numSides;
    for (int i = 0; i < numSides; ++i) {
        double angle = i * angleIncrement;
        int x = center.x() + radius * cos(angle);
        int y = center.y() + radius * sin(angle);
        addPoint(QPoint(x, y));
    }
}
