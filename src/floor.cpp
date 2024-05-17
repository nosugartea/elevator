#include "floor.h"
#include <cstdlib>
#include <ctime>

//int TFloor::numFloor = 1;

TFloor::TFloor()
{
}

TFloor::TFloor(int n, int f) :
    floorNum(n),
    maxFloors(f),
    maxWait(6),
    passengerVec(0, new TPassenger(maxFloors, floorNum))
{
}

int TFloor::genPassengers()
{
    std::srand(std::time(nullptr));
    int newPassenCount = 1;// не используется
    for (int i = 0; i < newPassenCount; ++i) {
        TPassenger* newPass = new TPassenger(maxFloors, floorNum);
        passengerVec.push_back(newPass);
    }
    return newPassenCount;
}

TFloor::~TFloor()
{
    for (TPassenger* passenger : passengerVec) {
        delete passenger;
    }
}
