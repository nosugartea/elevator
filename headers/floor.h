#ifndef TFLOOR_H
#define TFLOOR_H

#include "passenger.h"
#include <vector>

class TFloor
{
    int maxLiftCapacity; // грузоподъемность
    static int numFloor; // номер этажа
    int maxWait; // максимальное количество ожидающих пассажиров
    bool isGen; // флаг для старта генерациии пассажиров

    std::vector<TPassenger> passengerVec;

public:
    TFloor(int);
    void genPassengers(); // генерируем число новых пассажиров
};

int TFloor::numFloor = 1;

#endif // TFLOOR_H
