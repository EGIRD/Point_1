#ifndef RHOMBUS_H
#define RHOMBUS_H

#include "quadrilateral.h"

class Rhombus : public Quadrilateral {
public:
    Rhombus(const QPoint &center, int width, int height, const QColor &color);
};


#endif // RHOMBUS_H
