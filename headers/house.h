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

    void moveElevator(int);
    std::vector<TElevator*>& getElevatorVec();

public slots:
    void genPassengers();
    void onLiftMove(int floor) {
        qDebug() << "THouse >> Floor is now: Curr Floor" << floor;
        //emit senderFloorChanged(floor);
    }
    void goOnFloor(int) { moveElevator(1);};

signals:
    // Сигнал для отправки информации о создании пассажира
    void passengerGenerated(int floor); // ??
    void liftMove(int floor);
};

#endif // THOUSE_H
