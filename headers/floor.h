#ifndef TFLOOR_H
#define TFLOOR_H

#include "passenger.h"
#include <vector>

class TFloor
{
    int maxFloors; // максимальное количество этажей
    int maxWait; // максимальное количество ожидающих пассажиров

    std::vector<TPassenger> passengerVec;

public:
    TFloor(int);
    void genPassengers(); // генерируем число новых пассажиров
    static int numFloor; // номер этажа
};

#endif // TFLOOR_H
