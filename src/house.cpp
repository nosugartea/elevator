#include "house.h"
#include <cstdlib>
#include <ctime>
#include <QTimer>

THouse::THouse(int e,int f,int l) :
    maxEntrances(e),
    maxFloors(f),
    maxLiftCapacity(l),
    floorVecVec(maxEntrances, std::vector<TFloor>(maxFloors)),
    elevatorVec(maxEntrances)
{
    for (int i = 0; i < maxEntrances; ++i) {
        for (int j = 0; j < maxFloors; ++j) {
            floorVecVec[i][j] = TFloor(i+j+2, maxFloors);
        }
    }

    for (int i = 0; i < maxEntrances; ++i) {
        elevatorVec[i] = TElevator(maxLiftCapacity);
    }

    QTimer *timer = new QTimer();
    connect(timer, &QTimer::timeout, this, &THouse::genPassengers);
    timer->start(10000); // Интервал в миллисекундах
}

void THouse::moveElevator(int elevatorIndex) {
    if (elevatorIndex >= 0 && elevatorIndex < elevatorVec.size()) {
        elevatorVec[elevatorIndex].moveToFloor();
    }
}

std::vector<TElevator>& THouse::getElevatorVec() {
    return elevatorVec;
}

void THouse::genPassengers()
{
    std::srand(std::time(nullptr));
    int busyEntrance = 1 + std::rand() % maxEntrances;
    int busyFloor = 1 + std::rand() % maxFloors;
    TPassenger* p = floorVecVec[busyEntrance][busyFloor].genPassengers();

    emit passengerGenerated(p);
}
