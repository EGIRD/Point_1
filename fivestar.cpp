#include "fivestar.h"

FiveStar::FiveStar(const QPoint& center, int radius, const QColor& color)
    : Star(center, radius, radius * 0.4, 5, -M_PI_2, color) {}
