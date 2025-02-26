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

// star.cpp
bool Star::contains(const QPoint &point) const {
    QPolygon polygon;
    for (const QPoint &p : points) {
        polygon << p;
    }
    return polygon.containsPoint(point, Qt::OddEvenFill);
}

// QRect Star::boundingRect() const {
//     int minX = points[0].x(), maxX = points[0].x();
//     int minY = points[0].y(), maxY = points[0].y();

//     for (const QPoint &p : points) {
//         if (p.x() < minX) minX = p.x();
//         if (p.x() > maxX) maxX = p.x();
//         if (p.y() < minY) minY = p.y();
//         if (p.y() > maxY) maxY = p.y();
//     }

//     return QRect(minX, minY, maxX - minX, maxY - minY);
// }
