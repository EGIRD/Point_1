#ifndef OCTSTAR_H
#define OCTSTAR_H
#include "star.h"

class OctStar : public Star {
public:
    OctStar(const QPoint& center, int radius, const QColor& color = Qt::black);
};

#endif // OCTSTAR_H
