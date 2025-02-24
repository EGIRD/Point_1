#ifndef SHAPE_H
#define SHAPE_H

#include <QPainter>
#include <QColor>
#include <QPoint>

class Shape {
public:
    Shape(const QColor &color) : color(color) {}
    virtual void draw(QPainter &painter) = 0; // Чисто виртуальный метод для отрисовки
    virtual double area() const = 0; // Площадь
    virtual double perimeter() const = 0; // Периметр
    virtual QPoint centerOfMass() const = 0; // Центр масс
    virtual ~Shape() = default; // Виртуальный деструктор

protected:
    QColor color;
};

#endif // SHAPE_H
