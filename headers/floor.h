#ifndef TFLOOR_H
#define TFLOOR_H

#include "passenger.h"
#include <vector>

class TFloor
{
    bool isGen;
    std::vector<TPassenger> passengerVec;
    void genPassengers(); // случайным образов в подъезде выбираем этаж ему выставляем флаг для генерации пассажиров

public:
    TFloor();
    void setFlagGen(bool); // isGen = f;
};

#endif // TFLOOR_H
