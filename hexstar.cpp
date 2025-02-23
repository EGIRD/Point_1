#include "hexstar.h"

HexStar::HexStar(const QPoint& center, int radius, const QColor& color)
    : Star(center,
           radius,        // outerRadius
           radius / 2,    // innerRadius
           6,             // numPoints
           -M_PI_2)       // startAngle (-90 градусов для горизонтальной верхней точки)
{}
