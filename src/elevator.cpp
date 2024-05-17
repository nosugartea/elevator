#include "elevator.h"

#include <QTimer>
#include <QEventLoop>
#include <algorithm>

TElevator::TElevator()
{}

TElevator::TElevator(int l) :
    maxLiftCapacity(l),
    currentFloor(0), // текущий этаж лифта
    targetFloor(0),
    reachingPoints(0), // этажи цели, для пассажиров
    state(0)
{
    setReachPoint(3);
    setReachPoint(2);
    setReachPoint(5);

    millisecondsPerFloor = 1000; // 1 секунда
}

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

void TElevator::moveElevator()
{
    // Если лифт уже на нужном этаже, не нужно ничего делать
    if (currentFloor == targetFloor) {
        return;
    }

    // Перемещаем лифт на следующий этаж
    if (state == 1) {
        currentFloor++;
    } else if (state == -1) {
        currentFloor--;
    }

    QEventLoop loop;
    QTimer timer;
    QObject::connect(&timer, &QTimer::timeout, &loop, &QEventLoop::quit);
    timer.start(millisecondsPerFloor);
    emit floorChanged(currentFloor);
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
    // поиск ближайшего этажа в соответствии с напрвлением лифта
    int closeFloorIndx = 0;
    targetFloor = reachingPoints[0];
    for (int i = 1; i < reachingPoints.size(); ++i) {
        int minDistance = abs(currentFloor - reachingPoints[closeFloorIndx]);
        int distance = abs(currentFloor - reachingPoints[i]);
        if (distance < minDistance) {
            if ((currentFloor - reachingPoints[i] < 0 && state == 1) ||
                (currentFloor - reachingPoints[i] > 0 && state == -1))
            {
                targetFloor = reachingPoints[i];
                closeFloorIndx = i;
            }
            if (state == 0) {
                targetFloor = reachingPoints[i];
            }
        }
    }

    // если лифт стоял, то устанавливаем ему напрвление движения
    if (state == 0 && !reachingPoints.empty()) {
        state = (targetFloor - currentFloor > 0) ? 1 : -1; // вычисляем напрвление движения
    }

    moveElevator();

    if (currentFloor == targetFloor) {
        reachingPoints.erase(std::remove(reachingPoints.begin(), reachingPoints.end(), targetFloor), reachingPoints.end());
    }

    if (reachingPoints.empty()) {
        state = 0;
    }
}
