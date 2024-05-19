#ifndef TPASSENGER_H
#define TPASSENGER_H

class TPassenger
{
    int destinationFloor; // номер этажа нужный пассажиру
public:
    TPassenger(int);
    int getDestinationFloor() const;
};

#endif // TPASSENGER_H
