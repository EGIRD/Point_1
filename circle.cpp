#include "circle.h"
#include <cmath>
#include <QDebug>

Circle::Circle(const QPoint &center, int radius, const QColor &color)
    : Shape(color), center(center), radius(radius) {
    if (radius <= 0) {
        qDebug() << "Ошибка: радиус круга должен быть положительным";
    }
}

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

bool Circle::contains(const QPoint &point) const {
    int dx = point.x() - center.x();
    int dy = point.y() - center.y();
    return (dx * dx + dy * dy) <= (radius * radius);
}

void Circle::move(int dx, int dy) {
    center.setX(center.x() + dx);
    center.setY(center.y() + dy);
}

void Circle::scale(double factor) {
    radius *= factor; // Масштабируем радиус
}
