#include "octstar.h"

OctStar::OctStar(const QPoint& center, int radius, const QColor& color)
    : Star(center, radius, radius * 0.4, 8, -M_PI_2, color) {}
