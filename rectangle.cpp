#include "rectangle.h"

Rectangle::Rectangle(const QPoint &topLeft, const QPoint &bottomRight, const QColor &color)
    : Quadrilateral(color) {
    addPoint(topLeft);
    addPoint(QPoint(bottomRight.x(), topLeft.y()));
    addPoint(bottomRight);
    addPoint(QPoint(topLeft.x(), bottomRight.y()));
}
