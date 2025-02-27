#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "circle.h"
#include "rectangle.h"
#include "square.h"
#include "rhombus.h"
#include "triangle.h"
#include "fivestar.h"
//#include "hexagon.h"
//#include "octagon.h"
#include "hexstar.h"
#include "octstar.h"

#include <QColorDialog>
#include <QPainter>
#include <QMouseEvent>
#include <QComboBox>
#include <QPushButton>
#include <QTimer>
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
    , selectedShapeIndex(-1)
{
    ui->setupUi(this);

    zoomInTimer = new QTimer(this);
    zoomOutTimer = new QTimer(this);

    zoomInTimer->setInterval(50); // Интервал для увеличения
    zoomOutTimer->setInterval(50); // Интервал для уменьшения

    connect(zoomInTimer, &QTimer::timeout, this, &MainWindow::zoomIn);
    connect(zoomOutTimer, &QTimer::timeout, this, &MainWindow::zoomOut);

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

    QPushButton *upButton = new QPushButton("↑", this);
    QPushButton *downButton = new QPushButton("↓", this);
    QPushButton *leftButton = new QPushButton("←", this);
    QPushButton *rightButton = new QPushButton("→", this);
    QPushButton *zoomInButton = new QPushButton("+", this);
    QPushButton *zoomOutButton = new QPushButton("-", this);

    // Устанавливаем размер кнопок-стрелок
    upButton->setFixedSize(40, 40);
    downButton->setFixedSize(40, 40);
    leftButton->setFixedSize(40, 40);
    rightButton->setFixedSize(40, 40);
    zoomInButton->setFixedSize(40, 40);
    zoomOutButton->setFixedSize(40, 40);

    // Создание горизонтального layout для ползунка и кнопок-стрелок
    QHBoxLayout *bottomLayout = new QHBoxLayout();
    bottomLayout->addWidget(leftButton);
    bottomLayout->addWidget(upButton);
    bottomLayout->addWidget(downButton);
    bottomLayout->addWidget(rightButton);
    bottomLayout->addWidget(zoomInButton);
    bottomLayout->addWidget(zoomOutButton);
    bottomLayout->setAlignment(Qt::AlignBottom); // Выравнивание по нижнему краю

    // Основной вертикальный layout
    QVBoxLayout *mainLayout = new QVBoxLayout();
    mainLayout->addLayout(buttonLayout); // Добавляем кнопки справа
    mainLayout->addStretch(); // Растягиваем пространство между кнопками и нижним layout
    mainLayout->addLayout(bottomLayout); // Добавляем нижний layout с ползунком и стрелками

    // Установка layout в центральный виджет
    QWidget *centralWidget = new QWidget(this);
    centralWidget->setLayout(mainLayout);
    setCentralWidget(centralWidget);

    // Подключение сигналов к слотам
    connect(shapeComboBox, QOverload<int>::of(&QComboBox::currentIndexChanged), this, &MainWindow::onShapeSelected);
    connect(clearButton, &QPushButton::clicked, this, &MainWindow::clearShapes);
    connect(colorButton, &QPushButton::clicked, this, &MainWindow::selectColor);
    connect(infoButton, &QPushButton::clicked, this, &MainWindow::toggleIngoDisplay);

    // Подключение сигналов от кнопок-стрелок
    connect(upButton, &QPushButton::clicked, this, &MainWindow::moveShapeUp);
    connect(downButton, &QPushButton::clicked, this, &MainWindow::moveShapeDown);
    connect(leftButton, &QPushButton::clicked, this, &MainWindow::moveShapeLeft);
    connect(rightButton, &QPushButton::clicked, this, &MainWindow::moveShapeRight);
    // Подключение сигнала от ползунка

    // Подключение кнопок к таймерам
    connect(zoomInButton, &QPushButton::pressed, zoomInTimer, QOverload<>::of(&QTimer::start));
    connect(zoomInButton, &QPushButton::released, zoomInTimer, &QTimer::stop);

    connect(zoomOutButton, &QPushButton::pressed, zoomOutTimer, QOverload<>::of(&QTimer::start));
    connect(zoomOutButton, &QPushButton::released, zoomOutTimer, &QTimer::stop);
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
    int dx = abs(endPoint.x() - startPoint.x()); // Абсолютное значение
    int dy = abs(endPoint.y() - startPoint.y()); // Абсолютное значение
    return static_cast<int>(std::hypot(dx, dy)); // Всегда положительное значение
}

void MainWindow::zoomIn() {
    if (selectedShapeIndex != -1) {
        shapes[selectedShapeIndex]->scale(1.05); // Увеличиваем на 5%
        update(); // Перерисовываем окно
    }
}

void MainWindow::zoomOut() {
    if (selectedShapeIndex != -1) {
        shapes[selectedShapeIndex]->scale(0.95); // Уменьшаем на 5%
        update(); // Перерисовываем окно
    }
}

// Создание фигур, зависящих от радиуса
Shape* MainWindow::createShapeBasedOnRadius(MainWindow::ShapeType type, const QPoint &center, int radius) {
    switch (type) {
    case CircleShape:
        return new Circle(center, radius, currentColor);
    // case HexagonShape:
    //     return new Hexagon(center, radius, currentColor);
    // case OctagonShape:
    //     return new Octagon(center, radius, currentColor);
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

    if (radius <= 0) {
        qDebug() << "Ошибка: радиус должен быть положительным";
        return nullptr;
    }

    switch (currentShapeType) {
    case RectangleShape:
        return new Rectangle(startPoint, endPoint, currentColor);
    case SquareShape: {
        int side = qMax(abs(width), abs(height));
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
    qDebug() << "Очистка списка фигур";
    for (auto shape : shapes) {
        delete shape; // Удаляем каждую фигуру
    }
    shapes.clear(); // Очищаем список
    selectedShapeIndex = -1; // Сбрасываем индекс выделенной фигуры
    update(); // Перерисовываем окно
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

void MainWindow::moveShapeUp() {
    if (selectedShapeIndex != -1) {
        qDebug() << "Перемещение фигуры вверх";
        Shape *shape = shapes[selectedShapeIndex];
        shape->move(0, -10); // Перемещаем фигуру вверх на 10 пикселей
        update(); // Перерисовываем окно
    } else {
        qDebug() << "Фигура не выделена";
    }
}
void MainWindow::moveShapeDown() {
    if (selectedShapeIndex != -1) {
        Shape *shape = shapes[selectedShapeIndex];
        shape->move(0, 10); // Перемещаем фигуру вниз на 10 пикселей
        update(); // Перерисовываем окно
    }
}

void MainWindow::moveShapeLeft() {
    if (selectedShapeIndex != -1) {
        Shape *shape = shapes[selectedShapeIndex];
        shape->move(-10, 0); // Перемещаем фигуру влево на 10 пикселей
        update(); // Перерисовываем окно
    }
}

void MainWindow::moveShapeRight() {
    if (selectedShapeIndex != -1) {
        Shape *shape = shapes[selectedShapeIndex];
        shape->move(10, 0); // Перемещаем фигуру вправо на 10 пикселей
        update(); // Перерисовываем окно
    }
}

void MainWindow::onSliderValueChanged(int value) {
    if (selectedShapeIndex != -1) {
        double scaleFactor = value / 100.0; // Преобразуем значение ползунка в коэффициент масштабирования
        qDebug() << "Масштабирование: коэффициент =" << scaleFactor;
        shapes[selectedShapeIndex]->scale(scaleFactor); // Масштабируем выделенную фигуру
        update(); // Перерисовываем окно
    }
}

// Обработка нажатия мыши
// mainwindow.cpp
void MainWindow::mousePressEvent(QMouseEvent *event) {
    if (event->button() == Qt::LeftButton) {
        // Снимаем выделение с предыдущей фигуры
        if (selectedShapeIndex != -1) {
            shapes[selectedShapeIndex]->resetColor(); // Возвращаем исходный цвет
            selectedShapeIndex = -1; // Сбрасываем индекс выделенной фигуры
            update(); // Перерисовываем окно
        }

        // Проверяем, какая фигура находится под курсором
        for (int i = 0; i < shapes.size(); ++i) {
            if (shapes[i]->contains(event->pos())) {
                shapes[i]->selectedShape(); // Выделяем новую фигуру
                selectedShapeIndex = i; // Сохраняем индекс выделенной фигуры
                update(); // Перерисовываем окно
                return;
            }
        }

        // Если фигура не выделена, начинаем рисование новой фигуры
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
        qDebug() << "Создание новой фигуры";
        endPoint = event->pos();
        isDrawing = false;

        int width = abs(endPoint.x() - startPoint.x());
        int height = abs(endPoint.y() - startPoint.y());
        int sideLength = qMax(width, height);
        QPoint center((startPoint.x() + endPoint.x()) / 2, (startPoint.y() + endPoint.y()) / 2);

        Shape *shape = createShape(center, width, height, sideLength);
        if (shape) {
            qDebug() << "Фигура создана, добавление в список";
            shapes.append(shape);
            update();
        } else {
            qDebug() << "Ошибка: фигура не создана";
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
