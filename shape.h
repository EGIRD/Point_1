#ifndef SHAPE_H
#define SHAPE_H

#include <QPainter>
#include <QColor>

class Shape {
public:
    Shape(const QColor &color) : color(color) {}
    virtual void draw(QPainter &painter) = 0; // Чисто виртуальный метод для отрисовки
    virtual ~Shape() = default; // Виртуальный деструктор

protected:
    QColor color;
};

#endif // SHAPE_H
