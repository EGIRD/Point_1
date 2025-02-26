#include "circle.h"
#include <cmath>

Circle::Circle(const QPoint &center, int radius, const QColor &color)
    : Shape(color), center(center), radius(radius) {}

void Circle::draw(QPainter &painter) {
    painter.setPen(color);
    QRect circleRect(center.x() - radius, center.y() - radius, 2 * radius, 2 * radius);
    painter.drawEllipse(circleRect);
}

double Circle::area() const {
    return M_PI * radius * radius;
}

double Circle::perimeter() const {
    return 2 * M_PI * radius;
}

QPoint Circle::centerOfMass() const {
    return center;
}

// // circle.cpp
bool Circle::contains(const QPoint &point) const {
    int dx = point.x() - center.x();
    int dy = point.y() - center.y();
    return (dx * dx + dy * dy) <= (radius * radius);
}

void Circle::move(int dx, int dy) {
    center.setX(center.x() + dx);
    center.setY(center.y() + dy);
}

// QRect Circle::boundingRect() const {
//     return QRect(center.x() - radius, center.y() - radius, 2 * radius, 2 * radius);
// }
