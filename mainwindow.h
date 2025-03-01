#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "shape.h"

#include <QMainWindow>
#include <QPushButton>
#include <QColorDialog>
#include <QVBoxLayout>
#include <QMouseEvent>
#include <QComboBox>
#include <QPainter>
#include <QVector>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    // Перечисление для типов фигур
    enum ShapeType {
        RectangleShape,
        TriangleShape,
        CircleShape,
        RhombusShape,
        SquareShape,
        HexagonShape,
        OctagonShape,
        FiveStarShape,
        HexStarShape,
        OctStarShape
    };

    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

protected:
    void mousePressEvent(QMouseEvent *event) override; // Обработка нажатия мыши
    void mouseMoveEvent(QMouseEvent *event) override; // Обработка движения мыши
    void mouseReleaseEvent(QMouseEvent *event) override; // Обработка отпускания мыши
    void paintEvent(QPaintEvent *event) override; // Отрисовка фигур

private slots:
    void onShapeSelected(int index); // Слот для выбора фигуры
    void clearShapes(); // Очистка всех фигур
    void selectColor(); // Выбор цвета
    void toggleIngoDisplay(); // Переключение отображения информации
    void moveShapeUp();
    void moveShapeDown();
    void moveShapeLeft();
    void moveShapeRight();
    void onSliderValueChanged(int value);
    void zoomIn(); // Увеличение фигуры
    void zoomOut();

private:
    // Метод для создания фигуры
    Shape* createShape(const QPoint &center, int width, int height, int sideLength);

    // Новые методы для рефакторинга
    int calculateRadius(const QPoint &startPoint, const QPoint &endPoint) const; // Вычисление радиуса
    Shape* createShapeBasedOnRadius(MainWindow::ShapeType type, const QPoint &center, int radius); // Создание фигур, зависящих от радиуса

private:
    Ui::MainWindow *ui;
    QVector<Shape*> shapes; // Вектор фигур
    QPoint startPoint; // Начальная точка для рисования
    QPoint endPoint; // Конечная точка для рисования
    bool isDrawing; // Флаг для отслеживания рисования
    bool showInfo; // Флаг для отображения информации о фигурах
    QTimer *zoomInTimer; // Таймер для увеличения
    QTimer *zoomOutTimer;

    int selectedShapeIndex = -1; // Индекс выделенной фигуры
    void selectShape(const QPoint &point);

    ShapeType currentShapeType; // Текущий тип фигуры
    QColor currentColor; // Текущий цвет фигуры

    // Элементы интерфейса
    QComboBox *shapeComboBox; // Выпадающий список для выбора фигуры
    QPushButton *colorButton; // Кнопка выбора цвета
    QPushButton *clearButton; // Кнопка очистки
    QPushButton *infoButton; // Кнопка отображения информации
};

#endif // MAINWINDOW_H
