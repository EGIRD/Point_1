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

double RegularPolygon::area() const {
    return (numSides * radius * radius * sin(2 * M_PI / numSides)) / 2;
}

double RegularPolygon::perimeter() const {
    return numSides * 2 * radius * sin(M_PI / numSides);
}

QPoint RegularPolygon::centerOfMass() const {
    return center;
}
