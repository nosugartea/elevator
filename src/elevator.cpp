#include "elevator.h"

#include <QTimer>
#include <QEventLoop>
#include <algorithm>

TElevator::TElevator(int l) :
    maxLiftCapacity(l),
    currentFloor(0), // текущий этаж лифта
    targetFloor(0),
    reachingPoints(0), // этажи цели, для пассажиров
    state(0),
    doorIsOpen(true)
{
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
    doorIsOpen = false;
    emit floorChanged(currentFloor);

    QEventLoop loop;
    QTimer::singleShot(1000, &loop, SLOT(quit()));
    loop.exec();
}

void TElevator::setReachPoint(int destinationFloors)
{
    reachingPoints.push_back(destinationFloors);
    std::sort(reachingPoints.begin(), reachingPoints.end()); // сортировка по возрастанию
}

bool TElevator::moveToFloor()
{
    // поиск ближайшего этажа в соответствии с напрвлением лифта
    int closeFloorIndx = 0;
    targetFloor = reachingPoints[0];
    for (int i = 1; i < reachingPoints.size(); ++i) {
        int minDistance = abs(currentFloor - reachingPoints[closeFloorIndx]);
        int distance = abs(currentFloor - reachingPoints[i]);
        if (distance < minDistance) {
            if ((currentFloor < reachingPoints[i] && state == 1) ||
                (currentFloor > reachingPoints[i] && state == -1))
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

    if (currentFloor - targetFloor < 0 && state == -1) {
        state = 1;
    }

    if (currentFloor - targetFloor > 0 && state == 1) {
        state = -1;
    }

    moveElevator();

    bool onFloor = false;
    if (currentFloor == targetFloor) {
        reachingPoints.erase(std::remove(reachingPoints.begin(), reachingPoints.end(), targetFloor), reachingPoints.end());
        onFloor = true;
    }

    if (reachingPoints.empty()) {
        state = 0;
    }

    return onFloor;
}

int TElevator::getState()
{
    return state;
}

int TElevator::getCurrentFloor()
{
    return currentFloor;
}

int TElevator::getPassengerIn()
{
    return passengersIn.size();
}

void TElevator::setPassengerIn(TPassenger p)
{
    passengersIn.push_back(p);
}

bool TElevator::popPassenger(bool end)
{
    int sizeOld = passengersIn.size();
    if (end && !passengersIn.empty()) {
        passengersIn.erase(passengersIn.begin());
    } else if (!passengersIn.empty()) {
        auto it = std::find_if(passengersIn.begin(), passengersIn.end(), [=](const TPassenger& passenger) {
            return passenger.getDestinationFloor() == currentFloor;
        });
        if (it != passengersIn.end()) {
            passengersIn.erase(it);
        }
    }
    return sizeOld - passengersIn.size();
}

void TElevator::setDoorIsOpen(bool ok)
{
    doorIsOpen = ok;
}

bool TElevator::getDoorIsOpen()
{
    return doorIsOpen;
}

void TElevator::setDirection(int d)
{
    lastDirect = d;
}

int TElevator::getLastDirect()
{
    return lastDirect;
}

TElevator::~TElevator() {}
