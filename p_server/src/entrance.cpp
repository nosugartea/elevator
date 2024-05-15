#include "entrance.h"

TEntrance::TEntrance(int f, int l) :
    maxFloors(f),
    maxLiftCapacity(l),
    floorVec(maxFloors, TFloor(maxFloors)),
    elevator(maxLiftCapacity)
{}

void TEntrance::setBusyFloor(int busyFloor)
{
    floorVec[busyFloor].genPassengers();
}
