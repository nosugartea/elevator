#ifndef THOUSE_H
#define THOUSE_H

#include <QObject>
#include "floor.h"
#include "elevator.h"
#include <vector>
#include <QDebug>

class THouse :  public QObject
{
    Q_OBJECT

    int maxEntrances;
    int maxFloors;
    int maxLiftCapacity;

    std::vector<std::vector<TFloor*>> floorVecVec;
    std::vector<TElevator*> elevatorVec;

public:
    THouse(int, int, int);

    int getEntrancesCount();
    int getFloorsCount();
    void moveElevator(std::vector<int>, int);
    std::vector<TElevator*>& getElevatorVec();
    void resetParam(int, int, int);
    int getElevatorCapacity(int entrance) { return elevatorVec[entrance]->getCapacity(); }
    int getElevatorState(int entrance) { return elevatorVec[entrance]->getState(); }
    bool getElevatorDoors(int entrance) {return elevatorVec[entrance]->getDoorIsOpen(); }

public slots:
    void genPassengers();
    void onLiftMove(int floor) {
        qDebug() << "THouse >> Floor is now: Curr Floor" << floor;
    }
    // void goOnFloor(int) { moveElevator(1);};

signals:
    void liftMove(int floor);
    void passengerIn(int direction, int entrance, int floor);
    void openDoors(int);
};

#endif // THOUSE_H
