#ifndef TELEVATOR_H
#define TELEVATOR_H

#include <vector>
#include <QObject>
#include <QTimer>
#include <passenger.h>

class TElevator : public QObject
{
    Q_OBJECT

    int maxLiftCapacity;
    int currentFloor;
    int targetFloor;
    std::vector<int> reachingPoints;
    int state;
    int lastDirect;
    bool doorIsOpen;
    int millisecondsPerFloor;
    std::vector<TPassenger> passengersIn;

private slots:
    void moveElevator();

public:
    TElevator(int);
    ~TElevator();

    TElevator& operator=(const TElevator&);

    int getState();
    void setReachPoint(int);
    bool moveToFloor();
    int getCurrentFloor();
    int getPassengerIn();
    void setPassengerIn(TPassenger p);
    bool popPassenger(bool end);
    void setDoorIsOpen(bool ok);
    bool getDoorIsOpen();
    void setDirection(int d);
    int getLastDirect();

signals:
    void floorChanged(int floor); // Сигнал для отправки информации об изменении этажа
};

#endif // TELEVATOR_H
