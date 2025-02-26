#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "circle.h"
#include "rectangle.h"
#include "square.h"
#include "rhombus.h"
#include "triangle.h"
#include "fivestar.h"
#include "hexagon.h"
#include "octagon.h"
#include "hexstar.h"
#include "octstar.h"

#include <QColorDialog>
#include <QPainter>
#include <QMouseEvent>
#include <QComboBox>
#include <QPushButton>
#include <QVBoxLayout>
#include <cmath>
#include <QRect>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , isDrawing(false)
    , showInfo(false)
    , currentShapeType(RectangleShape)
    , currentColor(Qt::black)
{
    ui->setupUi(this);

    // Инициализация выпадающего списка для выбора фигуры
    shapeComboBox = new QComboBox(this);
    shapeComboBox->addItem("Прямоугольник");
    shapeComboBox->addItem("Квадрат");
    shapeComboBox->addItem("Ромб");
    shapeComboBox->addItem("Шестиугольник");
    shapeComboBox->addItem("Восьмиугольник");
    shapeComboBox->addItem("Треугольник");
    shapeComboBox->addItem("Круг");
    shapeComboBox->addItem("5-конечная звезда");
    shapeComboBox->addItem("6-конечная звезда");
    shapeComboBox->addItem("8-конечная звезда");
    shapeComboBox->setFixedSize(130, 40);

    // Инициализация кнопок
    clearButton = new QPushButton("Очистить", this);
    clearButton->setFixedSize(130, 40);

    colorButton = new QPushButton("Палитра", this);
    colorButton->setFixedSize(130, 40);

    infoButton = new QPushButton("Информация\nфигуры", this);
    infoButton->setFixedSize(130, 40);
    infoButton->setCheckable(true);

    // Создание layout для кнопок
    QVBoxLayout *buttonLayout = new QVBoxLayout();
    buttonLayout->addWidget(shapeComboBox);
    buttonLayout->addWidget(clearButton);
    buttonLayout->addWidget(colorButton);
    buttonLayout->addWidget(infoButton);
    buttonLayout->setAlignment(Qt::AlignTop | Qt::AlignRight);

    // Установка layout в центральный виджет
    QWidget *centralWidget = new QWidget(this);
    centralWidget->setLayout(buttonLayout);
    setCentralWidget(centralWidget);

    // Подключение сигналов к слотам
    connect(shapeComboBox, QOverload<int>::of(&QComboBox::currentIndexChanged), this, &MainWindow::onShapeSelected);
    connect(clearButton, &QPushButton::clicked, this, &MainWindow::clearShapes);
    connect(colorButton, &QPushButton::clicked, this, &MainWindow::selectColor);
    connect(infoButton, &QPushButton::clicked, this, &MainWindow::toggleIngoDisplay);
}

MainWindow::~MainWindow()
{
    for (auto shape : shapes) {
        delete shape;
    }
    delete ui;
}

// Вычисление радиуса на основе начальной и конечной точек
int MainWindow::calculateRadius(const QPoint &startPoint, const QPoint &endPoint) const {
    return static_cast<int>(std::hypot(endPoint.x() - startPoint.x(), endPoint.y() - startPoint.y()));
}

// Создание фигур, зависящих от радиуса
Shape* MainWindow::createShapeBasedOnRadius(MainWindow::ShapeType type, const QPoint &center, int radius) {
    switch (type) {
    case CircleShape:
        return new Circle(center, radius, currentColor);
    case HexagonShape:
        return new Hexagon(center, radius, currentColor);
    case OctagonShape:
        return new Octagon(center, radius, currentColor);
    case FiveStarShape:
        return new FiveStar(center, radius, currentColor);
    case HexStarShape:
        return new HexStar(center, radius, currentColor);
    case OctStarShape:
        return new OctStar(center, radius, currentColor);
    default:
        return nullptr;
    }
}

// Создание фигуры в зависимости от выбранного типа
Shape* MainWindow::createShape(const QPoint &center, int width, int height, int ) {
    int radius = calculateRadius(startPoint, endPoint);

    switch (currentShapeType) {
    case RectangleShape:
        return new Rectangle(startPoint, endPoint, currentColor);
    case SquareShape: {
        int side = qMax(width, height);
        return new Square(center, side, currentColor);
    }
    case RhombusShape:
        return new Rhombus(center, width, height, currentColor);
    case TriangleShape: {
        QPoint topPoint(startPoint.x(), startPoint.y());
        return new Triangle(topPoint, QPoint(2 * startPoint.x() - endPoint.x(), endPoint.y()), QPoint(endPoint.x(), endPoint.y()), currentColor);
    }
    default:
        return createShapeBasedOnRadius(currentShapeType, center, radius);
    }
}

// Обработка выбора фигуры в выпадающем списке
void MainWindow::onShapeSelected(int index) {
    switch (index) {
    case 0:
        currentShapeType = RectangleShape;
        break;
    case 1:
        currentShapeType = SquareShape;
        break;
    case 2:
        currentShapeType = RhombusShape;
        break;
    case 3:
        currentShapeType = HexagonShape;
        break;
    case 4:
        currentShapeType = OctagonShape;
        break;
    case 5:
        currentShapeType = TriangleShape;
        break;
    case 6:
        currentShapeType = CircleShape;
        break;
    case 7:
        currentShapeType = FiveStarShape;
        break;
    case 8:
        currentShapeType = HexStarShape;
        break;
    case 9:
        currentShapeType = OctStarShape;
        break;
    }
}

// Очистка всех фигур
void MainWindow::clearShapes() {
    for (auto shape : shapes) {
        delete shape;
    }
    shapes.clear();
    update();
}

// Выбор цвета
void MainWindow::selectColor() {
    QColor color = QColorDialog::getColor(currentColor, this, "Выберите цвет");
    if (color.isValid()) {
        currentColor = color;
    }
}

// Переключение отображения информации о фигурах
void MainWindow::toggleIngoDisplay() {
    showInfo = infoButton->isChecked();
    update();
}

// Обработка нажатия мыши
// mainwindow.cpp
void MainWindow::mousePressEvent(QMouseEvent *event) {
    if (event->button() == Qt::LeftButton) {
        for (int i = 0; i < shapes.size(); ++i) {
            if (shapes[i]->contains(event->pos())) {
                shapes[i]->selectedShape();
                update(); // Перерисовка окна
                return;
            }
        }
        startPoint = event->pos();
        isDrawing = true;
    }
}

void MainWindow::selectShape(const QPoint &point) {
    for (int i = 0; i < shapes.size(); ++i) {
        if (shapes[i]->contains(point)) {
            shapes[i]->selectedShape();
            update(); // Перерисовка окна
            return;
        }
    }
    selectedShapeIndex = -1; // Если ни одна фигура не выделена
    update();
}

// Обработка движения мыши
void MainWindow::mouseMoveEvent(QMouseEvent *event) {
    if (isDrawing) {
        endPoint = event->pos();
        update();
    }
}

// Обработка отпускания мыши
void MainWindow::mouseReleaseEvent(QMouseEvent *event) {
    if (event->button() == Qt::LeftButton && isDrawing) {
        endPoint = event->pos();
        isDrawing = false;

        int width = abs(endPoint.x() - startPoint.x());
        int height = abs(endPoint.y() - startPoint.y());
        int sideLength = qMax(width, height);
        QPoint center((startPoint.x() + endPoint.x()) / 2, (startPoint.y() + endPoint.y()) / 2);

        Shape *shape = createShape(center, width, height, sideLength);
        if (shape) {
            shapes.append(shape);
            update();
        }
    }
}

// Отрисовка фигур
// mainwindow.cpp
void MainWindow::paintEvent(QPaintEvent *event) {
    Q_UNUSED(event);
    QPainter painter(this);

    // Отрисовка всех фигур
    for (auto shape : shapes) {
        shape->draw(painter);

        // Отображение информации о фигуре, если включено
        if (showInfo) {
            QString info = QString("Площадь: %1\nПериметр: %2\nЦентр масс: (%3, %4)")
                               .arg(shape->area())
                               .arg(shape->perimeter())
                               .arg(shape->centerOfMass().x())
                               .arg(shape->centerOfMass().y());
            QStringList lines = info.split("\n");

            QPoint textPosition = shape->centerOfMass() + QPoint(20, 20);
            for (const QString& line : lines) {
                painter.drawText(textPosition, line);
                textPosition.setY(textPosition.y() + 15);
            }
        }
    }

    // Отрисовка текущей фигуры (если рисуем)
    if (isDrawing) {
        int width = abs(endPoint.x() - startPoint.x());
        int height = abs(endPoint.y() - startPoint.y());
        QPoint center((startPoint.x() + endPoint.x()) / 2, (startPoint.y() + endPoint.y()) / 2);

        Shape *tempShape = createShape(center, width, height, qMin(width, height));
        if (tempShape) {
            tempShape->draw(painter);
            delete tempShape; // Удаляем временную фигуру
        }
    }
}
