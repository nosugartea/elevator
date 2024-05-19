#ifndef TPASSENGER_H
#define TPASSENGER_H

class TPassenger
{
    int destinationFloor; // номер этажа нужный пассажиру
public:
    TPassenger(int);
    int getDestinationFloor() const { return destinationFloor; }
};

#endif // TPASSENGER_H
