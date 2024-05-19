#ifndef TELEVATOR_H
#define TELEVATOR_H

#include <vector>
#include <QObject>
#include <QTimer>
#include <passenger.h>

class TElevator : public QObject
{
    Q_OBJECT

    int maxLiftCapacity; // грузоподъемность
    int currentFloor; // текущий этаж лифта
    int targetFloor; // этаж куда едем
    std::vector<int> reachingPoints; // этажи цели, для пассажиров
    int state; // 0 - стоим, 1 - едем вверх, -1 - едем вниз
    int lastDirect;
    bool doorIsOpen;
    int millisecondsPerFloor; // Время, которое требуется на перемещение на один этаж
    std::vector<TPassenger> passengersIn;

private slots:
    void moveElevator();

public:
    TElevator();
    TElevator(int);
    TElevator& operator=(const TElevator&);

    // void move(); // использует currentFloor, maxPassengerCount, state, reachingPoints
    int getState() { return state; }
    void setReachPoint(int); // reachingPoints.push_back(p);
    bool moveToFloor();
    int getCurrentFloor() { return currentFloor; }
    int getPassengerIn() { return passengersIn.size(); }
    void setPassengerIn(TPassenger p) { passengersIn.push_back(p); }
    bool popPassenger(bool end)
    {
        int sizeOld = passengersIn.size();
        if (end && !passengersIn.empty()) {
            passengersIn.erase(passengersIn.begin());
        } else if (!passengersIn.empty()) {
            auto it = std::find_if(passengersIn.begin(), passengersIn.end(), [=](const TPassenger& passenger) {
                return passenger.getDestinationFloor() == currentFloor;
            });
            if (it != passengersIn.end()) {
                passengersIn.erase(it);
            }
        }
        return sizeOld - passengersIn.size();
    }
    void setDoorIsOpen(bool ok) { doorIsOpen = ok; }
    bool getDoorIsOpen() { return doorIsOpen; }
    void setDirection(int d) { lastDirect = d;}
    int getLastDirect() { return lastDirect; }

signals:
    void floorChanged(int floor); // Сигнал для отправки информации об изменении этажа
};

#endif // TELEVATOR_H
