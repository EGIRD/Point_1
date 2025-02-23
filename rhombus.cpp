#include "rhombus.h"

Rhombus::Rhombus(const QPoint &center, int width, int height, const QColor &color)
    : Quadrilateral(color) {
    addPoint(QPoint(center.x(), center.y() - height / 2)); // Верхняя точка
    addPoint(QPoint(center.x() + width / 2, center.y())); // Правая точка
    addPoint(QPoint(center.x(), center.y() + height / 2)); // Нижняя точка
    addPoint(QPoint(center.x() - width / 2, center.y())); // Левая точка
}
