#include "triangle.h"
#include <cmath>

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

double Triangle::area() const {
    int x1 = points[0].x(), y1 = points[0].y();
    int x2 = points[1].x(), y2 = points[1].y();
    int x3 = points[2].x(), y3 = points[2].y();
    return abs((x1*(y2 - y3) + x2*(y3 - y1) + x3*(y1 - y2)) / 2.0);
}

double Triangle::perimeter() const {
    double side1 = std::hypot(points[0].x() - points[1].x(), points[0].y() - points[1].y());
    double side2 = std::hypot(points[1].x() - points[2].x(), points[1].y() - points[2].y());
    double side3 = std::hypot(points[2].x() - points[0].x(), points[2].y() - points[0].y());
    return side1 + side2 + side3;
}

QPoint Triangle::centerOfMass() const {
    int x = (points[0].x() + points[1].x() + points[2].x()) / 3;
    int y = (points[0].y() + points[1].y() + points[2].y()) / 3;
    return QPoint(x, y);
}

bool Triangle::contains(const QPoint &point) const {
    QPolygon polygon;
    for (const QPoint &p : points) {
        polygon << p;
    }
    return polygon.containsPoint(point, Qt::OddEvenFill);
}

void Triangle::move(int dx, int dy) {
    for (QPoint &point : points) {
        point.setX(point.x() + dx);
        point.setY(point.y() + dy);
    }
}
