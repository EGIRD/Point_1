#ifndef SHAPE_H
#define SHAPE_H

#include <QPainter>
#include <QColor>
#include <QPoint>

class Shape {
public:
    Shape(const QColor &color) : color(color), originalColor(color) {}
    virtual void draw(QPainter &painter) = 0; // Чисто виртуальный метод для отрисовки
    virtual double area() const = 0; // Площадь
    virtual double perimeter() const = 0; // Периметр
    virtual QPoint centerOfMass() const = 0; // Центр масс
    virtual ~Shape() = default; // Виртуальный деструктор
    virtual bool contains(const QPoint &point) const = 0;
    virtual void move(int dx, int dy) = 0;

    void selectedShape() {
        color = Qt::blue; // Меняем цвет на зеленый
    }

    void resetColor() {
        color = originalColor; // Возвращаем исходный цвет
    }


protected:
    QColor color;
    QColor originalColor;
};

#endif // SHAPE_H
