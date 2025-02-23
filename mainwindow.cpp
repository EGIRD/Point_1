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
        int sideLength = qMax(width, height); // Для квадрата и круга
        QPoint center((startPoint.x() + endPoint.x()) / 2, (startPoint.y() + endPoint.y()) / 2);

        // Создаем фигуру в зависимости от выбранного типа
        Shape *shape = createShape(center, width, height, sideLength);

        if (shape) {
            shapes.append(shape); // Добавляем фигуру в список
            update(); // Обновляем экран
        }
    }
}

Shape* MainWindow::createShape(const QPoint &center, int width, int height, int sideLength) {
    switch (currentShapeType) {
    case RectangleShape:
        return new Rectangle(startPoint, endPoint, currentColor);
    case SquareShape:
        return new Square(startPoint, sideLength, currentColor);
    case RhombusShape:
        return new Rhombus(center, width, height, currentColor);
    case TriangleShape: {
        QPoint topPoint(startPoint.x(), startPoint.y()); // Верхняя точка
        return  new Triangle(topPoint, QPoint(2 * startPoint.x() -  endPoint.x(), endPoint.y()), QPoint(endPoint.x(), endPoint.y()), currentColor);
    }
    case CircleShape: {
        int radius = static_cast<int>(std::hypot(endPoint.x() - startPoint.x(), endPoint.y() - startPoint.y()));
        return new Circle(startPoint, radius, currentColor);
    }
    case HexagonShape: {
         int radius = static_cast<int>(std::hypot(endPoint.x() - startPoint.x(), endPoint.y() - startPoint.y()));
        return new Hexagon(startPoint, radius, currentColor);
    }
    case OctagonShape: {
        int radius = static_cast<int>(std::hypot(endPoint.x() - startPoint.x(), endPoint.y() - startPoint.y()));
        return new Octagon(startPoint, radius, currentColor);
    }
    case StarShape:
        return new Star(center, sideLength / 2, sideLength / 4, 5, currentColor); // 5-конечная звезда
    default:
        return nullptr;
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
        Shape *tempShape = nullptr; // Временный указатель на фигуру
        int width = abs(endPoint.x() - startPoint.x());
        int height = abs(endPoint.y() - startPoint.y());
        QPoint center((startPoint.x() + endPoint.x()) / 2, (startPoint.y() + endPoint.y()) / 2);

        switch (currentShapeType) {
        case RectangleShape:
            tempShape = new Rectangle(startPoint, endPoint, currentColor);
            break;
        case SquareShape:
            tempShape = new Square(startPoint, qMin(width, height), currentColor);
            break;
        case RhombusShape:
            tempShape = new Rhombus(center, width, height, currentColor);
            break;
        case TriangleShape: {
            QPoint topPoint(startPoint.x(), startPoint.y()); // Верхняя точка
            tempShape =  new Triangle(topPoint, QPoint(2 * startPoint.x() -  endPoint.x(), endPoint.y()), QPoint(endPoint.x(), endPoint.y()), currentColor);
            break;
        }
        case CircleShape: {
            int radius = static_cast<int>(std::hypot(endPoint.x() - startPoint.x(), endPoint.y() - startPoint.y()));
            tempShape = new Circle(startPoint, radius, currentColor);
            break;
        }
        case HexagonShape: {
            int radius = static_cast<int>(std::hypot(endPoint.x() - startPoint.x(), endPoint.y() - startPoint.y()));
            tempShape = new Hexagon(startPoint, radius, currentColor);
            break;
        }
        case OctagonShape: {
            int radius = static_cast<int>(std::hypot(endPoint.x() - startPoint.x(), endPoint.y() - startPoint.y()));
            tempShape = new Octagon(startPoint, radius, currentColor);
            break;
        }
        case StarShape:
            tempShape = new Star(center, qMin(width, height) / 2, qMin(width, height) / 4, 5, currentColor);
            break;
        }

        if (tempShape) {
            tempShape->draw(painter); // Используем метод draw для временной фигуры
            delete tempShape; // Освобождаем память
        }
    }
}
