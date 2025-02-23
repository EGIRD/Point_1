#include "square.h"

Square::Square(const QPoint &center, int sideLength, const QColor &color)
    : Rectangle(QPoint(center.x() - sideLength / 2, center.y() - sideLength / 2),
                QPoint(center.x() + sideLength / 2, center.y() + sideLength / 2), color) {}
void Square::draw(QPainter &painter) {
    painter.setPen(color);
    painter.drawPolygon(points.data(), points.size()); // Рисуем квадрат
}
