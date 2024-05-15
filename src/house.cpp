#include "house.h"
#include <cstdlib>
#include <ctime>
#include <QTimer>

THouse::THouse(int e,int f,int l) :
    maxEntrances(e),
    maxFloors(f),
    maxLiftCapacity(l),
    floorVecVec(maxEntrances, std::vector<TFloor>(maxFloors, maxFloors)),
    elevatorVec(maxEntrances, maxLiftCapacity)
{
    QTimer *timer = new QTimer();
    connect(timer, &QTimer::timeout, this, &THouse::genPassengers);
    timer->start(10000); // Интервал в миллисекундах
}

void THouse::moveElevator(int elevatorIndex, int floor) {
    if (elevatorIndex >= 0 && elevatorIndex < elevatorVec.size()) {
        elevatorVec[elevatorIndex].moveToFloor(floor);
    }
}

void THouse::genPassengers()
{
    std::srand(std::time(nullptr));
    int busyEntrance = 1 + std::rand() % maxEntrances;
    int busyFloor = 1 + std::rand() % maxFloors;
    floorVecVec[busyEntrance][busyFloor].genPassengers();

    emit passengerGenerated();
}
