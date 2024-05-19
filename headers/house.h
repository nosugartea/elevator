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
    int getElevatorCapacity(int entrance) { return elevatorVec[entrance]->getPassengerIn(); }
    int getElevatorState(int entrance) { return elevatorVec[entrance]->getState(); }
    bool getElevatorDoors(int entrance) {return elevatorVec[entrance]->getDoorIsOpen(); }
    void setPassenger(int en, int cf, int df, int count)
    {
        int newPass = floorVecVec[en][cf]->setPassengers(df, count);
        emit showPassenger(en, df, cf, newPass);
    }
    void setDirection(int en, int d) { elevatorVec[en]->setDirection(d);}
    bool emptyElevator(int en) { return !elevatorVec[en]->getPassengerIn(); }

public slots:
    void onLiftMove(int floor) {
        qDebug() << "THouse >> Floor is now: Curr Floor" << floor;
    }

signals:
    void showPassenger(int entrance, int dest, int appear, int count);
    void liftMove(int floor);
    void passengerIn(int direction, int entrance, int floor);
    void passengerOut(int entrance);
    void openDoors(int);
};

#endif // THOUSE_H
