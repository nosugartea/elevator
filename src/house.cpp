#include "house.h"
#include <cstdlib>
#include <ctime>

THouse::THouse(int e,int f,int l) :
    maxEntrances(e),
    maxFloors(f),
    maxLiftCapacity(l),
    entranceVec(maxEntrances, TEntrance(maxFloors, maxLiftCapacity))
{}

void THouse::genPassengers()
{
    std::srand(std::time(nullptr));
    int busyEntrance = 1 + std::rand() % maxEntrances;
    int busyFloor = 1 + std::rand() % maxFloors;
    entranceVec[busyEntrance].setBusyFloor(busyFloor); // floorVec[busyFloor].setFlagGen(true);
}
