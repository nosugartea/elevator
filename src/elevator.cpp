#include "elevator.h"

#include <QTimer>

TElevator::TElevator(int l) :
    maxLiftCapacity(l),
    currentFloor(1), // текущий этаж лифта
    reachingPoints(0), // этажи цели, для пассажиров
    state(0)
{}

void TElevator::move()
{

}

void TElevator::setState(char s)
{
    state = s;
}

void TElevator::setReachPoint(int destinationFloors)
{

}

void TElevator::moveToFloor(int floor)
{
    int floorsToMove = qAbs(currentFloor - floor); // Вычисляем количество этажей для перемещения

    // Если лифт уже на нужном этаже, не нужно ничего делать
    if (floorsToMove == 0)
        return;

    // Вычисляем время, которое требуется на перемещение на один этаж
    int millisecondsPerFloor = 1000; // 1 секунда
    int totalMilliseconds = floorsToMove * millisecondsPerFloor;

    // Создаем таймер для перемещения лифта
    QTimer *timer = new QTimer();
    connect(timer, &QTimer::timeout, [=]() {
        // Перемещаем лифт на следующий этаж
        if (currentFloor < floor) {
            currentFloor++;
        } else {
            currentFloor--;
        }

        // Если лифт достиг нужного этажа, останавливаем таймер и отправляем сигнал
        if (currentFloor == floor) {
            timer->stop();
            emit floorChanged(currentFloor);
        }
    });

    // Запускаем таймер с заданным временем
    timer->start(totalMilliseconds / floorsToMove);
}
