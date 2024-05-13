#ifndef TELEVATOR_H
#define TELEVATOR_H

#include <vector>

class TElevator
{
    int currentFloor; // текущий этаж личфта
    int maxPassengerCount; // грузоподъемность
    std::vector<int> reachingPoints; // этажи, для пассажиров
    char state;

public:
    TElevator();

    void move(); // использует currentFloor, maxPassengerCount, state, reachingPoints
    void setState(char); // state = s;
    void setReachPoint(int); // reachingPoints.push_back(p);
};

#endif // TELEVATOR_H
