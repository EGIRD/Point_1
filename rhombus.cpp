#include "rhombus.h"

Rhombus::Rhombus(const QPoint &center, int width, int height, const QColor &color)
    : Polygon(color) {
    addPoint(QPoint(center.x(), center.y() - height / 2)); // Верхняя точка
    addPoint(QPoint(center.x() + width / 2, center.y())); // Правая точка
    addPoint(QPoint(center.x(), center.y() + height / 2)); // Нижняя точка
    addPoint(QPoint(center.x() - width / 2, center.y())); // Левая точка
}

void Rhombus::draw(QPainter &painter) {
    painter.setPen(color);
    painter.drawPolygon(points.data(), points.size());
}

double Rhombus::area() const {
    int width = points[1].x() - points[3].x();
    int height = points[2].y() - points[0].y();
    return (width * height) / 2.0;
}

double Rhombus::perimeter() const {
    double side = std::hypot(points[1].x() - points[0].x(), points[1].y() - points[0].y());
    return 4 * side;
}

QPoint Rhombus::centerOfMass() const {
    return QPoint((points[0].x() + points[2].x()) / 2, (points[0].y() + points[2].y()) / 2);
}
