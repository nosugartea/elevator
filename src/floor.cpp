#include "floor.h"
#include <cstdlib>
#include <ctime>

int TFloor::numFloor = 1;

TFloor::TFloor(int f) :
    maxFloors(f),
    maxWait(6),
    passengerVec(0, TPassenger(maxFloors, numFloor))
{
}

void TFloor::genPassengers()
{
    std::srand(std::time(nullptr));
    int newPassenCount = 0 + std::rand() % 2;
    for (int i = 0; i < newPassenCount; ++i) {
        TPassenger newPass(maxFloors, numFloor);
        passengerVec.push_back(newPass);
    }
}
