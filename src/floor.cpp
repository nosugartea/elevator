#include "floor.h"

TFloor::TFloor()
{
}

TFloor::TFloor(int n, int f) :
    floorNum(n),
    maxFloors(f),
    passengerVec(0, new TPassenger(0)),
    passengersUp(0),
    passengersDown(0)
{}

TFloor::~TFloor()
{
    for (TPassenger* passenger : passengerVec) {
        delete passenger;
    }
}
