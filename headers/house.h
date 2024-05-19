#ifndef THOUSE_H
#define THOUSE_H

#include <QObject>
#include "floor.h"
#include "elevator.h"
#include <vector>

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
    ~THouse();

    int getEntrancesCount();
    int getFloorsCount();
    void moveElevator(std::vector<int>, int);
    std::vector<TElevator*>& getElevatorVec();
    void resetParam(int, int, int);
    int getElevatorCapacity(int entrance);
    int getElevatorState(int entrance);
    bool getElevatorDoors(int entrance);
    void setPassenger(int en, int cf, int df, int count);
    void setDirection(int en, int d);
    bool emptyElevator(int en);

signals:
    void showPassenger(int entrance, int dest, int appear, int count);
    void liftMove(int floor);
    void passengerIn(int direction, int entrance, int floor);
    void passengerOut(int entrance);
    void openDoors(int);
    void elevatorArrived(int);
};

#endif // THOUSE_H
