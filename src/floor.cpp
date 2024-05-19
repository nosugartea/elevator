#include "floor.h"

TFloor::TFloor()
{
}

TFloor::TFloor(int n, int f) :
    floorNum(n),
    maxFloors(f),
    maxWait(6),
    passengerVec(0, new TPassenger(0))
{}

TFloor::~TFloor()
{
    for (TPassenger* passenger : passengerVec) {
        delete passenger;
    }
}
