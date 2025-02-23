#include "octagon.h"

Octagon::Octagon(const QPoint &center, int radius, const QColor &color)
    : RegularPolygon(center, radius, 8, color) {}

void Octagon::draw(QPainter &painter) {
    painter.setPen(color);
    RegularPolygon::draw(painter); // Вызываем draw базового класса
}
