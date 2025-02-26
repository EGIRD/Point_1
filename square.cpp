#include "square.h"

Square::Square(const QPoint &center, int sideLength, const QColor &color)
    : Rectangle(QPoint(center.x() - sideLength / 2, center.y() - sideLength / 2),
                QPoint(center.x() + sideLength / 2, center.y() + sideLength / 2), color) {}

double Square::area() const {
    int side = points[1].x() - points[0].x();
    return side * side;
}

double Square::perimeter() const {
    int side = points[1].x() - points[0].x();
    return 4 * side;
}

QPoint Square::centerOfMass() const {
    return QPoint((points[0].x() + points[2].x()) / 2, (points[0].y() + points[2].y()) / 2);
}

// square.cpp
bool Square::contains(const QPoint &point) const {
    return point.x() >= points[0].x() && point.x() <= points[2].x() &&
           point.y() >= points[0].y() && point.y() <= points[2].y();
}

// QRect Square::boundingRect() const {
//     return QRect(points[0], points[2]);
// }
