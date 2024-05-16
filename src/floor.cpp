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
    passengerVec(0, TPassenger(maxFloors, floorNum))
{
}

TPassenger* TFloor::genPassengers()
{
    TPassenger* p = nullptr;
    std::srand(std::time(nullptr));
    int newPassenCount = 0 + std::rand() % 1;
    for (int i = 0; i < newPassenCount; ++i) {
        TPassenger newPass(maxFloors, floorNum);
        passengerVec.push_back(newPass);
        p = &newPass;
    }
    return p;
}
