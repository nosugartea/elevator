#ifndef TELEVATOR_H
#define TELEVATOR_H

#include <vector>

class TElevator
{
    int maxLiftCapacity; // грузоподъемность
    int currentFloor; // текущий этаж лифта
    std::vector<int> reachingPoints; // этажи цели, для пассажиров
    char state;

public:
    TElevator(int);

    void move(); // использует currentFloor, maxPassengerCount, state, reachingPoints
    void setState(char); // state = s;
    void setReachPoint(int); // reachingPoints.push_back(p);
};

#endif // TELEVATOR_H
