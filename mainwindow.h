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
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

protected:
    void mousePressEvent(QMouseEvent *event) override; // Обработка нажатия мыши
    void mouseMoveEvent(QMouseEvent *event) override; // Обработка движения мыши
    void mouseReleaseEvent(QMouseEvent *event) override; // Обработка отпускания мыши
    void paintEvent(QPaintEvent *event) override; // Отрисовка фигур

private slots:
    void onShapeSelected(int index);//слот для выбора фигуры
    void clearShapes();
    void selectColor();
    void toggleIngoDisplay();

private:
    Shape* createShape(const QPoint &center, int width, int height, int sideLength);

private:
    Ui::MainWindow *ui;
    QVector<Shape*> shapes; // Вектор фигур
    QPoint startPoint; // Начальная точка для рисования
    QPoint endPoint; // Конечная точка для рисования
    bool isDrawing; // Флаг для отслеживания рисования
    bool showInfo; 

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
    // Тип фигуры
    ShapeType currentShapeType; // Текущий тип фигуры
    QColor currentColor;

    //выпадающий список для выбора фигуры
    QComboBox *shapeComboBox;
    QPushButton *colorButton;
    QPushButton *clearButton;
    QPushButton *infoButton;

};
#endif // MAINWINDOW_H
