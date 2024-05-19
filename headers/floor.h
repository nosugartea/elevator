#ifndef TFLOOR_H
#define TFLOOR_H

#include "passenger.h"
#include <vector>

class TFloor
{
    int floorNum;
    int maxFloors;
    std::vector<TPassenger*> passengerVec;
    int passengersUp;
    int passengersDown;

public:
    TFloor(int, int);
    ~TFloor();

    int getPassengersUp();
    int getPassengersDown();
    std::vector<TPassenger*> getPassengers();
    void deletePassenger(int floor);
    int setPassengers(int df, int count);
};

#endif // TFLOOR_H
