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

    std::vector<std::vector<TFloor>> floorVecVec;
    std::vector<TElevator> elevatorVec;

public:
    THouse(int, int, int);

    void moveElevator(int, int);

public slots:
    void genPassengers();

signals:
    // Сигнал для отправки информации о создании пассажира
    void passengerGenerated(); // ??
};

#endif // THOUSE_H
