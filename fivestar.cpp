#include "fivestar.h"
#include <cmath>

FiveStar::FiveStar(const QPoint& center, int radius, const QColor& color)
    : Star(center,
           radius,        // outerRadius
           radius * 0.4,  // innerRadius (можно регулировать пропорции)
           5,             // numPoints (5-конечная звезда)
           -M_PI_2)       // startAngle (-90 градусов для горизонтальной верхней точки)
{}
