#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "circle.h"
#include "rectangle.h"
#include "square.h"
#include "rhombus.h"
#include "triangle.h"
#include "hexagon.h"
#include "octagon.h"
#include "star.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , isDrawing(false)
    , currentShapeType(RectangleShape)
    , currentColor(Qt::black)
{
    ui->setupUi(this);

    shapeComboBox = new QComboBox(this);
    shapeComboBox->addItem("Прямоугольник");
    shapeComboBox->addItem("Квадрат");
    shapeComboBox->addItem("Ромб");
    shapeComboBox->addItem("Шестиугольник");
    shapeComboBox->addItem("Восьмиугольник");
    shapeComboBox->addItem("Звезда");
    shapeComboBox->addItem("Треугольник");
    shapeComboBox->addItem("Круг");
    shapeComboBox->setFixedSize(130,40);

    clearButton = new QPushButton("Очистить", this);
    clearButton->setFixedSize(130,40);

    colorButton = new QPushButton("Палитра", this);
    colorButton->setFixedSize(130,40);

    // Создаем layout для кнопок
    QVBoxLayout *buttonLayout = new QVBoxLayout();
    buttonLayout->addWidget(shapeComboBox);
    buttonLayout->addWidget(clearButton);
    buttonLayout->addWidget(colorButton);
    buttonLayout->setAlignment(Qt::AlignTop | Qt::AlignRight); // Размещаем в правом верхнем углу

    // Создаем центральный виджет и устанавливаем layout
    QWidget *centralWidget = new QWidget(this);
    centralWidget->setLayout(buttonLayout);
    setCentralWidget(centralWidget);

    // Подключение кнопок к слотам
    connect(shapeComboBox, QOverload<int>::of(&QComboBox::currentIndexChanged),this,&MainWindow::onShapeSelected);
    connect(clearButton, &QPushButton::clicked, this, &MainWindow::clearShapes);
    connect(colorButton, &QPushButton::clicked, this, &MainWindow::selectColor);
}

MainWindow::~MainWindow()
{
    for (auto shape : shapes) {
        delete shape;
    }
    delete ui;
}

void MainWindow::onShapeSelected(int index) {
    switch (index) {
    case 0:
        currentShapeType = RectangleShape; // Прямоугольник
        break;
    case 1:
        currentShapeType = SquareShape; // Квадрат
        break;
    case 2:
        currentShapeType = RhombusShape; // Ромб
        break;
    case 3:
        currentShapeType = HexagonShape; // Шестиугольник
        break;
    case 4:
        currentShapeType = OctagonShape; // Восьмиугольник
        break;
    case 5:
        currentShapeType = StarShape; // Звезда
        break;
    case 6:
        currentShapeType = TriangleShape; // Треугольник
        break;
    case 7:
        currentShapeType = CircleShape; // Круг
        break;
    }
}

void MainWindow::clearShapes(){
    for(auto shape : shapes){
        delete shape;
    }
    shapes.clear();
    update();
}

void MainWindow::selectColor(){
    QColor color = QColorDialog::getColor(currentColor,this, "Выберите цвет");
    if (color.isValid()) {
        currentColor = color;
    }
}

void MainWindow::mousePressEvent(QMouseEvent *event) {
    if (event->button() == Qt::LeftButton) {
        startPoint = event->pos(); // Начальная точка
        isDrawing = true; // Начинаем рисование
    }
}

void MainWindow::mouseMoveEvent(QMouseEvent *event) {
    if (isDrawing) {
        endPoint = event->pos(); // Обновляем конечную точку
        update(); // Перерисовываем экран
    }
}

void MainWindow::mouseReleaseEvent(QMouseEvent *event) {
    if (event->button() == Qt::LeftButton && isDrawing) {
        endPoint = event->pos(); // Конечная точка
        isDrawing = false; // Завершаем рисование

        // Вычисляем размеры фигуры
        int width = abs(endPoint.x() - startPoint.x());
        int height = abs(endPoint.y() - startPoint.y());
        int sideLength = qMin(width, height); // Для квадрата и круга
        QPoint center((startPoint.x() + endPoint.x()) / 2, (startPoint.y() + endPoint.y()) / 2);

        // Создаем фигуру в зависимости от выбранного типа
        Shape *shape = nullptr;
        switch (currentShapeType) {
        case RectangleShape:
            shape = new Rectangle(startPoint, endPoint, currentColor);
            break;
        case SquareShape:
            shape = new Square(startPoint, sideLength, currentColor);
            break;
        case RhombusShape:
            shape = new Rhombus(center, width, height, currentColor);
            break;
        case TriangleShape: {
            QPoint topPoint((startPoint.x() + endPoint.x()) / 2, startPoint.y()); // Верхняя точка
            shape = new Triangle(topPoint, QPoint(startPoint.x(), endPoint.y()), QPoint(endPoint.x(), endPoint.y()), currentColor);
            break;
        }
        case CircleShape:
            shape = new Circle(center, sideLength / 2, currentColor);
            break;
        case HexagonShape:
            shape = new Hexagon(center, sideLength / 2, currentColor);
            break;
        case OctagonShape:
            shape = new Octagon(center, sideLength / 2, currentColor);
            break;
        case StarShape:
            shape = new Star(center, sideLength / 2, sideLength / 4, 5, currentColor); // 5-конечная звезда
            break;
        }

        if (shape) {
            shapes.append(shape); // Добавляем фигуру в список
            update(); // Обновляем экран
        }
    }
}

void MainWindow::paintEvent(QPaintEvent *event) {
    Q_UNUSED(event);
    QPainter painter(this);

    // Отрисовка всех фигур
    for (auto shape : shapes) {
        shape->draw(painter);
    }

    // Отрисовка текущей фигуры (если рисуем)
    if (isDrawing) {
        painter.setPen(currentColor); // Устанавливаем текущий цвет
        int width = abs(endPoint.x() - startPoint.x());
        int height = abs(endPoint.y() - startPoint.y());
        QPoint center((startPoint.x() + endPoint.x()) / 2, (startPoint.y() + endPoint.y()) / 2);

        switch (currentShapeType) {
        case RectangleShape:
            painter.drawRect(QRect(startPoint, endPoint)); // Рисуем прямоугольник
            break;
        case SquareShape: {
            int sideLength = qMin(width, height);
            painter.drawRect(QRect(startPoint, QSize(sideLength, sideLength))); // Рисуем квадрат
            break;
        }
        case RhombusShape: {
            QPoint top(center.x(), center.y() - height / 2);
            QPoint right(center.x() + width / 2, center.y());
            QPoint bottom(center.x(), center.y() + height / 2);
            QPoint left(center.x() - width / 2, center.y());
            QPoint points[4] = { top, right, bottom, left };
            painter.drawPolygon(points, 4); // Рисуем ромб
            break;
        }
        case TriangleShape: {
            QPoint topPoint((startPoint.x() + endPoint.x()) / 2, startPoint.y()); // Верхняя точка
            QPoint bottomLeft(startPoint.x(), endPoint.y()); // Левая нижняя точка
            QPoint bottomRight(endPoint.x(), endPoint.y()); // Правая нижняя точка
            QPoint points[3] = { topPoint, bottomLeft, bottomRight };
            painter.drawPolygon(points, 3); // Рисуем треугольник
            break;
        }
        case CircleShape:
            painter.drawEllipse(center, width / 2, height / 2); // Рисуем круг
            break;
        case HexagonShape: {
            int radius = qMin(width, height) / 2;
            QVector<QPoint> hexPoints;
            double angleIncrement = 2 * M_PI / 6; // 6 вершин
            for (int i = 0; i < 6; ++i) {
                double angle = i * angleIncrement;
                int x = center.x() + radius * cos(angle);
                int y = center.y() + radius * sin(angle);
                hexPoints.append(QPoint(x, y));
            }
            painter.drawPolygon(hexPoints.data(), hexPoints.size()); // Рисуем шестиугольник
            break;
        }
        case OctagonShape: {
            int radius = qMin(width, height) / 2;
            QVector<QPoint> octPoints;
            double angleIncrement = 2 * M_PI / 8; // 8 вершин
            for (int i = 0; i < 8; ++i) {
                double angle = i * angleIncrement;
                int x = center.x() + radius * cos(angle);
                int y = center.y() + radius * sin(angle);
                octPoints.append(QPoint(x, y));
            }
            painter.drawPolygon(octPoints.data(), octPoints.size()); // Рисуем восьмиугольник
            break;
        }
        case StarShape: {
            int outerRadius = qMin(width, height) / 2;
            int innerRadius = outerRadius / 2;
            QVector<QPoint> starPoints;
            double angleIncrement = 2 * M_PI / 5; // 5-конечная звезда
            for (int i = 0; i < 5; ++i) {
                double outerAngle = i * angleIncrement;
                int x = center.x() + outerRadius * cos(outerAngle);
                int y = center.y() + outerRadius * sin(outerAngle);
                starPoints.append(QPoint(x, y));

                double innerAngle = outerAngle + angleIncrement / 2;
                x = center.x() + innerRadius * cos(innerAngle);
                y = center.y() + innerRadius * sin(innerAngle);
                starPoints.append(QPoint(x, y));
            }
            painter.drawPolygon(starPoints.data(), starPoints.size()); // Рисуем звезду
            break;
            }
        }
    }
}
