#include "hexagon.h"

Hexagon::Hexagon(const QPoint &center, int radius, const QColor &color)
    : RegularPolygon(center, radius, 6, color) {}
