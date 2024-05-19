#include "state.h"

#include <QPainter>
#include <QLinearGradient>

TState::TState(int e, int f, QWidget *parent)
    : QWidget(parent), entrances(e), floors(f)
{
    for (int i = 0; i < entrances; ++i) {
        elevatorsPosition.push_back(0);
    }

    for (int i = 0; i < entrances; ++i){
        passengerUP.resize(entrances);
        passengerDOWN.resize(entrances);
        for (int j = 0; j < floors; ++j) {
            passengerUP[i].push_back(0);
        }

        for (int j = 0; j < floors; ++j) {
            passengerDOWN[i].push_back(0);
        }
    }

    for (int i = 0; i < entrances; ++i) {
        elevatorsPassengersIn.push_back(0);
    }

    for (int i = 0; i < entrances; ++i) {
        elevatorsState.push_back(0);
    }

    for (int i = 0; i < entrances; ++i) {
        elevatorsDoors.push_back(true);
    }
}

TState::~TState()
{
}

void TState::paintEvent(QPaintEvent*)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    // Определение размеров и положения этажей
    int numColumns = entrances; // количество столбцов
    int numFloors = floors; // количество этажей в каждом столбце
    int floorWidth = 100;// ширина прямоугольника и квадрата
    int floorHeight = 50; // высота прямоугольника
    int squareSize = floorHeight; // сторона квадрата

    // Установка цвета пера для рамки
    QPen pen(Qt::black);
    painter.setPen(pen);

    // Рисование этажей
    for (int col = 0; col < numColumns; ++col) {
        int x1 = col * (floorHeight + floorWidth); // начальная позиция прямоугольника по x
        QLinearGradient gradient(x1, 0, x1 + floorWidth, floorHeight);
        gradient.setColorAt(0, QColor("#58CDAE"));
        gradient.setColorAt(1, QColor("#3CB37B"));
        painter.fillRect(x1, 0, floorWidth + squareSize, floorHeight, gradient);
        painter.drawRect(x1, 0, floorWidth + squareSize, floorHeight); // рисование рамки
        painter.drawText(x1 + 5, floorHeight / 2, QString("Подъезд %1").arg(col + 1));

        for (int i = 0; i < numFloors; ++i) {
            int y1 = (1 + i) * floorHeight; // позиция прямоугольника по y
            int x2 = x1 + floorWidth; // начальная позиция квадрата по x
            int y2 = y1; // позиция квадрата по y

            // Рисование квадрата
            painter.fillRect(x2, y2, squareSize, squareSize, Qt::white);
            painter.drawRect(x2, y2, squareSize, squareSize); // рисование рамки
            painter.drawText(x2 + 5, y2 + squareSize / 2, QString("U %1 D %2").arg(passengerUP[col][floors - i - 1]).arg(passengerDOWN[col][floors - i - 1]));

            if (floors - elevatorsPosition[col] == i + 1) {
                QLinearGradient gradient(x1, y1, x1 + floorWidth, y1 + floorHeight);
                if (elevatorsDoors[col] == false)
                {
                    gradient.setColorAt(0, QColor("#58CDAE"));
                    gradient.setColorAt(1, QColor("#3CB37B"));
                } else {
                    gradient.setColorAt(0, QColor("#FFE5CC"));
                    gradient.setColorAt(1, QColor("#FFFF99"));
                }

                painter.fillRect(x1, y1, floorWidth, floorHeight, gradient);

                painter.drawRect(x1, y1, floorWidth, floorHeight); // рисование рамки
                painter.drawText(x1 + 5, y1 + floorHeight / 2, QString("Пассажиры %1").arg(elevatorsPassengersIn[col]));
                continue;
            }

            // Рисование прямоугольника
            painter.fillRect(x1, y1, floorWidth, floorHeight, Qt::white);
            painter.drawRect(x1, y1, floorWidth, floorHeight); // рисование рамки
            painter.drawText(x1 + 5, y1 + floorHeight / 2, QString("Floor %1").arg(numFloors - i));
        }
    }
}

void TState::closeEvent(QCloseEvent *event)
{
    emit closed();
    QWidget::closeEvent(event);
}

void TState::setNewParam(int e, int f)
{
    entrances = e;
    floors = f;

    elevatorsPosition.clear();
    passengerUP.clear();
    passengerDOWN.clear();
    elevatorsPassengersIn.clear();
    elevatorsState.clear();
    elevatorsDoors.clear();

    for (int i = 0; i < entrances; ++i) {
        elevatorsPosition.push_back(0);
    }

    for (int i = 0; i < entrances; ++i){
        passengerUP.resize(entrances);
        passengerDOWN.resize(entrances);
        for (int j = 0; j < floors; ++j) {
            passengerUP[i].push_back(0);
        }

        for (int j = 0; j < floors; ++j) {
            passengerDOWN[i].push_back(0);
        }
    }

    for (int i = 0; i < entrances; ++i) {
        elevatorsPassengersIn.push_back(0);
    }

    for (int i = 0; i < entrances; ++i) {
        elevatorsState.push_back(0);
    }

    for (int i = 0; i < entrances; ++i) {
        elevatorsDoors.push_back(0);
    }
}

void TState::moveElevator(int entrance, int floor, int passengersIn, int state, bool doors)
{
    elevatorsState[entrance] = state;
    elevatorsDoors[entrance] = doors;
    elevatorsPosition[entrance] = floor;
    elevatorsPassengersIn[entrance] = passengersIn;
    update();
}

void TState::showPassenger(int entrance, int dest, int appear, int count)
{
    QChar direct;
    if (appear < dest)
    {
        passengerUP[entrance][appear] += count;
        direct = 'U';
    } else if (appear > dest) {
        passengerDOWN[entrance][appear] += count;
        direct = 'D';
    }
    update();
}

void TState::clearFloor(int direction, int entrance, int floor)
{
    if (direction == 1) {
        --passengerUP[entrance][floor];
    } else if (direction == -1) {
        --passengerDOWN[entrance][floor];
    }
    ++elevatorsPassengersIn[entrance];
    update();
}

void TState::clearElevator(int entrance)
{
    --elevatorsPassengersIn[entrance];
    update();
}

void TState::openDoor(int entrance)
{
    elevatorsDoors[entrance] = true;
    update();
}
