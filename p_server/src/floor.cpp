#include "floor.h"
#include <cstdlib>
#include <ctime>

TFloor::TFloor(int l) :
    maxLiftCapacity(l),
    maxWait(6),
    isGen(false),
    passengerVec(0, TPassenger(maxLiftCapacity, numFloor))
{
}

void TFloor::genPassengers()
{
    std::srand(std::time(nullptr));
    int newPassenCount = 1 + std::rand() % 2;
    for (int i = 0 + passengerVec.size(); i < newPassenCount; ++i) {
        TPassenger newPass(maxLiftCapacity, numFloor);
        passengerVec.push_back(newPass);
    }
}
