#include "passenger.h"
#include <cstdlib>
#include <ctime>

TPassenger::TPassenger(int mf, int cf) : maxFloors(mf), currentFloor(cf)
{
    std::srand(std::time(nullptr));
    destinationFloor = currentFloor;
    while (destinationFloor == currentFloor) {
        destinationFloor = 1 + std::rand() % maxFloors;
    }

    if (destinationFloor < currentFloor) {
        direction = 0;
    } else {
        direction = 1;
    }
}
