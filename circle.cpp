#include "circle.h"

Circle::Circle(const QPoint &center, int radius, const QColor &color)
    : Shape(color), center(center), radius(radius) {}

void Circle::draw(QPainter &painter) {
    painter.setPen(color); // Устанавливаем цвет контура
    QRect circleRect(center.x() - radius, center.y() - radius, 2 * radius, 2 * radius);
    painter.drawEllipse(circleRect); // Рисуем круг
}
