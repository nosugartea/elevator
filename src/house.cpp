#include "house.h"
#include <QTimer>

THouse::THouse(int e,int f,int c) :
    maxEntrances(e),
    maxFloors(f),
    maxLiftCapacity(c),
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
}

int THouse::getEntrancesCount()
{
    return maxEntrances;
}

int THouse::getFloorsCount()
{
    return maxFloors;
}

void THouse::moveElevator(std::vector<int> destinFloors, int elevatorIndex) {
    if (elevatorIndex >= 0 && elevatorIndex < elevatorVec.size()) {
        for (int i = 0; i < destinFloors.size(); ++i) {
            elevatorVec[elevatorIndex]->setReachPoint(destinFloors[i] - 1);
        }

        do {
            int currFloor = elevatorVec[elevatorIndex]->getCurrentFloor();
            std::vector<TPassenger*> passengersWait = floorVecVec[elevatorIndex][currFloor]->getPassengers();
            if (!passengersWait.empty() && elevatorVec[elevatorIndex]->getPassengerIn() < maxLiftCapacity &&
                ((floorVecVec[elevatorIndex][currFloor]->getPassengersUp() && elevatorVec[elevatorIndex]->getState() == 1) ||
                 (floorVecVec[elevatorIndex][currFloor]->getPassengersDown() && elevatorVec[elevatorIndex]->getState() == -1)))
            {
                break;
            }
        } while (!elevatorVec[elevatorIndex]->moveToFloor());
        emit openDoors(elevatorIndex);

        while (elevatorVec[elevatorIndex]->popPassenger()) {
            emit passengerOut(elevatorIndex);
        }

        int currFloor = elevatorVec[elevatorIndex]->getCurrentFloor();
        std::vector<TPassenger*> passengersWait = floorVecVec[elevatorIndex][currFloor]->getPassengers();
        for (int i = 0; i < passengersWait.size(); ++i) {
            int goFloor = passengersWait[i]->getDestinationFloor();

            if (elevatorVec[elevatorIndex]->getPassengerIn() < maxLiftCapacity &&
                ((currFloor < goFloor &&  elevatorVec[elevatorIndex]->getState() == 1) ||
                 (currFloor > goFloor &&  elevatorVec[elevatorIndex]->getState() == -1) ||
                  elevatorVec[elevatorIndex]->getState() == 0)) {

                elevatorVec[elevatorIndex]->setPassengerIn(goFloor);
                floorVecVec[elevatorIndex][currFloor]->deletePassenger(goFloor);

                emit passengerIn(elevatorVec[elevatorIndex]->getLastDirect(), elevatorIndex, currFloor);
            }
        }
    }
}

std::vector<TElevator*>& THouse::getElevatorVec() {
    return elevatorVec;
}

void THouse::resetParam(int e, int f, int c)
{
    // Очистка векторов
    for (int i = 0; i < maxEntrances; ++i) {
        for (int j = 0; j < maxFloors; ++j) {
            delete floorVecVec[i][j];
        }
        floorVecVec[i].clear();
    }
    floorVecVec.clear();

    for (int i = 0; i < maxEntrances; ++i) {
        delete elevatorVec[i];
    }
    elevatorVec.clear();

    maxEntrances = e;
    maxFloors = f;
    maxLiftCapacity = c;

    // Меняем размеры на новые
    floorVecVec.resize(maxEntrances);
    for (int i = 0; i < maxEntrances; ++i) {
        floorVecVec[i].resize(maxFloors);
        for (int j = 0; j < maxFloors; ++j) {
            floorVecVec[i][j] = new TFloor(j, maxFloors);
        }
    }

    elevatorVec.resize(maxEntrances);
    for (int i = 0; i < maxEntrances; ++i) {
        elevatorVec[i] = new TElevator(maxLiftCapacity);
    }

    qDebug() << "House::resetParam >> " << floorVecVec.size() << " " << floorVecVec[0].size() << " " << maxLiftCapacity;
}
