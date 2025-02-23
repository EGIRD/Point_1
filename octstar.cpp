#include "octstar.h"

OctStar::OctStar(const QPoint& center, int radius, const QColor& color)
    : Star(center,
           radius,        // outerRadius
           radius * 0.4,  // innerRadius
           8,             // numPoints
           -M_PI_2)       // startAngle
{}
