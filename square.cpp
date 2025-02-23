#include "square.h"

Square::Square(const QPoint &topLeft, int sideLength, const QColor &color)
    : Rectangle(topLeft, QPoint(topLeft.x() + sideLength, topLeft.y() + sideLength), color) {}

void Square::draw(QPainter &painter) {
    painter.setPen(color);
    painter.drawPolygon(points.data(), points.size()); // Рисуем квадрат
}
