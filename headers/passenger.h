#ifndef TPASSENGER_H
#define TPASSENGER_H

class TPassenger
{
    int maxFloors; // количество этажей в подъезде
    int destinationFloor; // номер этажа нужный пассажиру
    int currentFloor; // текущий номер этажа ??
    char direction; // направление вверх/вниз куда нужно пассажиру
public:
    TPassenger(int);
    int getStartFloor() { return currentFloor; }
    int getDestinationFloor() const { return destinationFloor; }
};

#endif // TPASSENGER_H
