#ifndef FIVESTAR_H
#define FIVESTAR_H

#include "star.h"

class FiveStar : public Star {
public:
    FiveStar(const QPoint& center, int radius, const QColor& color = Qt::black);
};

#endif // FIVESTAR_H
