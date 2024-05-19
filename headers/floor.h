#ifndef TFLOOR_H
#define TFLOOR_H

#include "passenger.h"
#include <vector>
#include <algorithm>

class TFloor
{

    int floorNum; // номер этажа в подъезде
    int maxFloors; // максимальное количество этажей
    std::vector<TPassenger*> passengerVec;
    int passengersUp;
    int passengersDown;

public:
    TFloor();
    TFloor(int, int);

    ~TFloor();

    int getPassengersUp() { return passengersUp; }
    int getPassengersDown() { return passengersDown; }
    std::vector<TPassenger*> getPassengers() { return passengerVec; }
    void deletePassenger(int floor) {
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

    int setPassengers(int df, int count)
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
};

#endif // TFLOOR_H
