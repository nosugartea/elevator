#ifndef TENTRANCE_H
#define TENTRANCE_H

#include "floor.h"
#include "elevator.h"
#include <vector>

class TEntrance
{
    int maxFloors;
    int maxLiftCapacity;

    std::vector<TFloor> floorVec;
    TElevator elevator;

public:
    TEntrance(int, int);
    void setBusyFloor(int); // вызываем генерацию пассажиров на этаже
};

#endif // TENTRANCE_H
