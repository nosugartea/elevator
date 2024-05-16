#include "elevator.h"

#include <QTimer>
#include <algorithm>

TElevator::TElevator()
{}

TElevator::TElevator(int l) :
    maxLiftCapacity(l),
    currentFloor(1), // текущий этаж лифта
    reachingPoints(0), // этажи цели, для пассажиров
    state(0)
{}

TElevator& TElevator::operator=(const TElevator& other)
{
    if (this != &other) // Проверка на самоприсваивание
    {
        // Копируем данные из другого объекта
        maxLiftCapacity = other.maxLiftCapacity;
        currentFloor = other.currentFloor;
        reachingPoints = other.reachingPoints;
        state = other.state;
    }
    return *this;
}

void TElevator::move()
{

}

void TElevator::setState(char s)
{
    state = s;
}

void TElevator::setReachPoint(int destinationFloors)
{
    reachingPoints.push_back(destinationFloors);
    std::sort(reachingPoints.begin(), reachingPoints.end()); // сортировка по возрастанию
}

void TElevator::moveToFloor()
{
    int floor = 3; //reachingPoints[0];
    int state = (currentFloor - floor > 0 ? 1 : -1); // вычисляем напрвление движения
    int floorsToMove = qAbs(currentFloor - floor); // Вычисляем количество этажей для перемещения

    // Если лифт уже на нужном этаже, не нужно ничего делать
    if (floorsToMove == 0) {
        state = 0;
        return;
    }

    // Время, которое требуется на перемещение на один этаж
    int millisecondsPerFloor = 1000; // 1 секунда

    // Создаем таймер для перемещения лифта
    QTimer *timer = new QTimer();
    connect(timer, &QTimer::timeout, this, [=]() mutable {
        // Перемещаем лифт на следующий этаж
        if (state == 1) {
            currentFloor++;
        } else {
            currentFloor--;
        }

        emit floorChanged(currentFloor);
        timer->start(millisecondsPerFloor);

        // Если лифт достиг нужного этажа, останавливаем таймер и отправляем сигнал
        if (currentFloor == floor) {
            state = 0;
            timer->stop();
        }
    });
}
