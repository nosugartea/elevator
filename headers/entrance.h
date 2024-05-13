#ifndef TENTRANCE_H
#define TENTRANCE_H

#include "floor.h"
#include "elevator.h"
#include <vector>

class TEntrance
{
    std::vector<TFloor> floorVec;
    TElevator elevator;

    bool genFloor();
public:
    TEntrance();
};

#endif // TENTRANCE_H
