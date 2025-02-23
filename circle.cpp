#include "circle.h"

Circle::Circle(const QPoint &center, int radius, const QColor &color)
    : Shape(color), center(center), radius(radius) {}

void Circle::draw(QPainter &painter) {
    painter.setPen(color); // Устанавливаем цвет контура
    painter.drawEllipse(center, radius, radius); // Рисуем круг
}
