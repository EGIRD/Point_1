#include "square.h"

Square::Square(const QPoint &topLeft, int sideLength, const QColor &color)
    : Rectangle(topLeft, QPoint(topLeft.x() + sideLength, topLeft.y() + sideLength), color) {}
