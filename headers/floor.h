#ifndef TFLOOR_H
#define TFLOOR_H

#include "passenger.h"
#include <vector>

class TFloor
{
    int floorNum; // номер этажа в подъезде
    int maxFloors; // максимальное количество этажей
    int maxWait; // максимальное количество ожидающих пассажиров

    std::vector<TPassenger> passengerVec;

public:
    TFloor();
    TFloor(int, int);
    TPassenger* genPassengers(); // генерируем число новых пассажиров
};

#endif // TFLOOR_H
