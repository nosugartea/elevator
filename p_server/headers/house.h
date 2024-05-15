#ifndef THOUSE_H
#define THOUSE_H

#include "entrance.h"
#include <vector>

class THouse
{
    int maxEntrances;
    int maxFloors;
    int maxLiftCapacity;

    std::vector<TEntrance> entranceVec;

    void genPassengers();
public:
    THouse();
    THouse(int, int, int);
};

#endif // THOUSE_H
