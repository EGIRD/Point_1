#include "octagon.h"

Octagon::Octagon(const QPoint &center, int radius, const QColor &color)
    : RegularPolygon(center, radius, 8, color) {}
