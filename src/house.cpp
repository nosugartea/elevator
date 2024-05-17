#include "house.h"
#include <cstdlib>
#include <ctime>
#include <QTimer>

THouse::THouse(int e,int f,int l) :
    maxEntrances(e),
    maxFloors(f),
    maxLiftCapacity(l),
    floorVecVec(maxEntrances, std::vector<TFloor*>(maxFloors)),
    elevatorVec(maxEntrances)
{
    for (int i = 0; i < maxEntrances; ++i) {
        for (int j = 0; j < maxFloors; ++j) {
            floorVecVec[i][j] = new TFloor(j, maxFloors);
        }
    }

    for (int i = 0; i < maxEntrances; ++i) {
        elevatorVec[i] = new TElevator(maxLiftCapacity);
    }

    QTimer *timer = new QTimer();
    connect(timer, &QTimer::timeout, this, &THouse::genPassengers);
    timer->start(3000); // Интервал в миллисекундах
}

void THouse::moveElevator(int elevatorIndex) {
    if (elevatorIndex >= 0 && elevatorIndex < elevatorVec.size()) {
        elevatorVec[elevatorIndex]->moveToFloor();
    }
}

std::vector<TElevator*>& THouse::getElevatorVec() {
    return elevatorVec;
}

void THouse::genPassengers()
{
    std::srand(std::time(nullptr));
    int busyEntrance = 0 + std::rand() % maxEntrances;
    int busyFloor = 0 + std::rand() % maxFloors;
    int countNewPassenger = floorVecVec[busyEntrance][busyFloor]->genPassengers();
    if (countNewPassenger == 0)
        return;

    emit passengerGenerated(busyFloor);
}
