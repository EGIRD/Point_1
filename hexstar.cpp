#include "hexstar.h"

HexStar::HexStar(const QPoint& center, int radius, const QColor& color)
    : Star(center, radius, radius / 2, 6, -M_PI_2, color) {}
