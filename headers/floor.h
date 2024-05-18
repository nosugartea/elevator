#ifndef TFLOOR_H
#define TFLOOR_H

#include "passenger.h"
#include <vector>
#include <algorithm>

class TFloor
{
    int floorNum; // номер этажа в подъезде
    int maxFloors; // максимальное количество этажей
    int maxWait; // максимальное количество ожидающих пассажиров

    std::vector<TPassenger*> passengerVec;
    int passengersUp;
    int passengersDown;

public:
    TFloor();
    TFloor(int, int);

    ~TFloor();

    int genPassengers(); // генерируем число новых пассажиров
    int getPassengersUp() { return passengersUp; }
    int getPassengersDown() { return passengersDown; }
    std::vector<TPassenger*> getPassengers() { return passengerVec; }
    void deletePassenger(int floor) { passengerVec.erase(
            std::remove_if(passengerVec.begin(), passengerVec.end(), [floor](TPassenger* passenger) {
                if (passenger->getDestinationFloor() == floor) {
                    delete passenger;
                    return true;
                }
                return false;
            }),
            passengerVec.end()
            );
    }
};

#endif // TFLOOR_H
