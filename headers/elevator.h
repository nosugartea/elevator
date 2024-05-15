#ifndef TELEVATOR_H
#define TELEVATOR_H

#include <vector>
#include <QObject>

class TElevator : QObject
{
    int maxLiftCapacity; // грузоподъемность
    int currentFloor; // текущий этаж лифта
    std::vector<int> reachingPoints; // этажи цели, для пассажиров
    char state; // 0 - стоим, 1 - едем

public:
    TElevator(int);

    void move(); // использует currentFloor, maxPassengerCount, state, reachingPoints
    void setState(char); // state = s;
    void setReachPoint(int); // reachingPoints.push_back(p);
    void moveToFloor(int);
};

#endif // TELEVATOR_H
