#include "star.h"
#include <cmath>

Star::Star(const QPoint &center, int outerRadius, int innerRadius, int numPoints, const QColor &color)
    : Polygon(color), center(center), outerRadius(outerRadius), innerRadius(innerRadius), numPoints(numPoints) {
    double angleIncrement = 2 * M_PI / numPoints; // Угол между лучами
    for (int i = 0; i < numPoints; ++i) {
        // Внешняя точка
        double outerAngle = i * angleIncrement;
        int x = center.x() + outerRadius * cos(outerAngle);
        int y = center.y() + outerRadius * sin(outerAngle);
        addPoint(QPoint(x, y));

        // Внутренняя точка
        double innerAngle = outerAngle + angleIncrement / 2;
        x = center.x() + innerRadius * cos(innerAngle);
        y = center.y() + innerRadius * sin(innerAngle);
        addPoint(QPoint(x, y));
    }
}

void Star::draw(QPainter &painter) {
    painter.setPen(color); // Устанавливаем цвет контура
    painter.setBrush(color); // Устанавливаем цвет заливки
    painter.drawPolygon(points.data(), points.size()); // Рисуем звезду
}
