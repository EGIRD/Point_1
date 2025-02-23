#include "hexagon.h"

Hexagon::Hexagon(const QPoint &center, int radius, const QColor &color)
    : RegularPolygon(center, radius, 6, color) {}

 void Hexagon::draw(QPainter &painter) {
    painter.setPen(color);
    RegularPolygon::draw(painter); // Вызываем draw базового класса
}
