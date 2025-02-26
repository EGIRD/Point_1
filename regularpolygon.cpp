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

// regularpolygon.cpp
bool RegularPolygon::contains(const QPoint &point) const {
    QPolygon polygon;
    for (const QPoint &p : points) {
        polygon << p;
    }
    return polygon.containsPoint(point, Qt::OddEvenFill);
}

// QRect RegularPolygon::boundingRect() const {
//     if (points.isEmpty()) return QRect();

//     int minX = points[0].x(), maxX = points[0].x();
//     int minY = points[0].y(), maxY = points[0].y();

//     for (const QPoint &p : points) {
//         if (p.x() < minX) minX = p.x();
//         if (p.x() > maxX) maxX = p.x();
//         if (p.y() < minY) minY = p.y();
//         if (p.y() > maxY) maxY = p.y();
//     }

//     return QRect(minX, minY, maxX - minX, maxY - minY);
// }
