#ifndef HEXSTAR_H
#define HEXSTAR_H

#include "star.h"


class HexStar : public Star {
public:
    HexStar(const QPoint& center, int radius, const QColor& color = Qt::black);
};
#endif // HEXSTAR_H
