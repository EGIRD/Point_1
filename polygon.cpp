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

// // polygon.cpp
bool Polygon::contains(const QPoint &point) const {
    QPolygon polygon;
    for (const QPoint &p : points) {
        polygon << p;
    }
    return polygon.containsPoint(point, Qt::OddEvenFill);
}

// QRect Polygon::boundingRect() const {
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
