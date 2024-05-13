#ifndef PASSENGER_H
#define PASSENGER_H

class TPassenger
{
    int maxFloors; // количество этажей в подъезде
    int destinationFloor; // номер этажа нужный пассажиру
    int currentFloor; // текущий номер этажа ??
    char direction; // направление вверх/вниз куда нужно пассажиру
public:
    TPassenger(int, int);
};

#endif // PASSENGER_H
