#include "star.h"
#include <cmath>

Star::Star(const QPoint& center, int outerRadius, int innerRadius,
           int numPoints, double startAngle, const QColor& color)
    : Polygon(color), center(center), outerRadius(outerRadius),
    innerRadius(innerRadius), numPoints(numPoints), startAngle(startAngle) {
    calculatePoints(); // Вычисляем вершины звезды
}

void Star::calculatePoints() {
    double angleIncrement = 2 * M_PI / numPoints; // Угловой шаг между вершинами

    for (int i = 0; i < numPoints; ++i) {
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

double Star::area() const {
    // Площадь звезды вычисляется как сумма площадей треугольников
    double area = 0.0;
    for (int i = 0; i < points.size(); ++i) {
        const QPoint& p1 = points[i];
        const QPoint& p2 = points[(i + 1) % points.size()];
        area += (p1.x() * p2.y() - p2.x() * p1.y());
    }
    return abs(area) / 2.0;
}

double Star::perimeter() const {
    // Периметр звезды — сумма длин всех сторон
    double perimeter = 0.0;
    for (int i = 0; i < points.size(); ++i) {
        const QPoint& p1 = points[i];
        const QPoint& p2 = points[(i + 1) % points.size()];
        perimeter += std::hypot(p2.x() - p1.x(), p2.y() - p1.y());
    }
    return perimeter;
}

QPoint Star::centerOfMass() const {
    // Центр масс — среднее арифметическое всех вершин
    int sumX = 0, sumY = 0;
    for (const QPoint& point : points) {
        sumX += point.x();
        sumY += point.y();
    }
    return QPoint(sumX / points.size(), sumY / points.size());
}
