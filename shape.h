#ifndef SHAPE_H
#define SHAPE_H

#include <QPainter>
#include <QColor>
#include <QPoint>

class Shape {
public:
    Shape(const QColor &color) : color(color), originalColor(color) {}
    virtual void draw(QPainter &painter) = 0;
    virtual double area() const = 0;
    virtual double perimeter() const = 0;
    virtual QPoint centerOfMass() const = 0;
    virtual ~Shape() = default;
    virtual bool contains(const QPoint &point) const = 0;
    virtual void move(int dx, int dy) = 0;
    virtual void scale(double factor) = 0; // Масштабирование фигуры
    void selectedShape() {
        color = Qt::blue; // Меняем цвет на синий
    }
    void resetColor() {
        color = originalColor; // Возвращаем исходный цвет
    }

protected:
    QColor color;
    QColor originalColor; // Исходный цвет фигуры
};

#endif // SHAPE_H
