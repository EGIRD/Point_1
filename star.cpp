#include "star.h"
#include <cmath>

Star::Star(const QPoint& center, int outerRadius, int innerRadius,
           int numPoints, double startAngle, const QColor& color)
    : Polygon(color),
    center(center),
    outerRadius(outerRadius),
    innerRadius(innerRadius),
    numPoints(numPoints),
    startAngle(startAngle)
{
    calculatePoints();
}

void Star::calculatePoints() {
    double angleIncrement = 2 * M_PI / numPoints;

    for(int i = 0; i < numPoints; ++i) {
        // Внешняя точка
        double angle = startAngle + i * angleIncrement;
        int x = center.x() + outerRadius * cos(angle);
        int y = center.y() + outerRadius * sin(angle);
        addPoint(QPoint(x, y));

        // Внутренняя точка
        angle += angleIncrement / 2;
        x = center.x() + innerRadius * cos(angle);
        y = center.y() + innerRadius * sin(angle);
        addPoint(QPoint(x, y));
    }
}
