#ifndef TELEVATOR_H
#define TELEVATOR_H

#include <vector>
#include <QObject>
#include <QTimer>

class TElevator : public QObject
{
    Q_OBJECT

    int maxLiftCapacity; // грузоподъемность
    int passengersIn;
    int currentFloor; // текущий этаж лифта
    int targetFloor; // этаж куда едем
    std::vector<int> reachingPoints; // этажи цели, для пассажиров
    int state; // 0 - стоим, 1 - едем вверх, -1 - едем вниз
    bool doorIsOpen;
    int millisecondsPerFloor; // Время, которое требуется на перемещение на один этаж

private slots:
    void moveElevator();

public:
    TElevator();
    TElevator(int);
    TElevator& operator=(const TElevator&);

    // void move(); // использует currentFloor, maxPassengerCount, state, reachingPoints
    void setState(char); // state = s;
    int getState() { return state; }
    void setReachPoint(int); // reachingPoints.push_back(p);
    bool moveToFloor();
    int getCurrentFloor() { return currentFloor; }
    int getPassengerIn() { return passengersIn; }
    void setPassengerIn(int p) { passengersIn += p; }
    int getCapacity() { return passengersIn; }
    void setDoorIsOpen(bool ok) { doorIsOpen = ok; }
    bool getDoorIsOpen() { return doorIsOpen; }

signals:
    void floorChanged(int floor); // Сигнал для отправки информации об изменении этажа
};

#endif // TELEVATOR_H
