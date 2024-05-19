#include "floor.h"
#include <algorithm>

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
    passengerVec.clear();
}

int TFloor::getPassengersUp()
{
    return passengersUp;
}

int TFloor::getPassengersDown()
{
    return passengersDown;
}

std::vector<TPassenger*> TFloor::getPassengers()
{
    return passengerVec;
}

void TFloor::deletePassenger(int floor)
{
    auto it = std::find_if(passengerVec.begin(), passengerVec.end(),[floor](TPassenger* passenger) {
        return passenger->getDestinationFloor() == floor;
    });

    if (it != passengerVec.end()) {
        if (floor < floorNum) {
            --passengersDown;
        }
        if (floor > floorNum) {
            --passengersUp;
        }
        delete *it;
        passengerVec.erase(it);
    }
}

int TFloor::setPassengers(int df, int count)
{
    int oldCount = 0;
    for (TPassenger* pass: passengerVec) {
        if (pass->getDestinationFloor() == df) {
            ++oldCount;
        }
    }
    for (int i = 0; i < count - oldCount; ++i) {
        TPassenger* pass = new TPassenger(df);
        passengerVec.push_back(pass);
        if (df < floorNum) {
            ++passengersDown;
        } else if (df > floorNum) {
            ++passengersUp;
        }
    }
    return count - oldCount;
}
