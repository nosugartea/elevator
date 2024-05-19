#include "passenger.h"

TPassenger::TPassenger(int df) : destinationFloor(df)
{}

int TPassenger::getDestinationFloor() const
{
    return destinationFloor;
}
