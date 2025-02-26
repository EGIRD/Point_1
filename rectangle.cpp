#include "rectangle.h"

Rectangle::Rectangle(const QPoint &topLeft, const QPoint &bottomRight, const QColor &color)
    : Quadrilateral(color) {
    addPoint(topLeft);
    addPoint(QPoint(bottomRight.x(), topLeft.y()));
    addPoint(bottomRight);
    addPoint(QPoint(topLeft.x(), bottomRight.y()));
}

double Rectangle::area() const {
    int width = points[1].x() - points[0].x();
    int height = points[2].y() - points[1].y();
    return width * height;
}

double Rectangle::perimeter() const {
    int width = points[1].x() - points[0].x();
    int height = points[2].y() - points[1].y();

    return abs(2 * (width + height));
}

QPoint Rectangle::centerOfMass() const {
    int x = (points[0].x() + points[2].x()) / 2;
    int y = (points[0].y() + points[2].y()) / 2;
    return QPoint(x, y);
}

bool Rectangle::contains(const QPoint &point) const {
    return point.x() >= points[0].x() && point.x() <= points[2].x() &&
           point.y() >= points[0].y() && point.y() <= points[2].y();
}

void Rectangle::move(int dx, int dy) {
    for (QPoint &point : points) {
        point.setX(point.x() + dx);
        point.setY(point.y() + dy);
    }
}


