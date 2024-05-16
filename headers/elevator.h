#ifndef TELEVATOR_H
#define TELEVATOR_H

#include <vector>
#include <QObject>

class TElevator : QObject
{
    int maxLiftCapacity; // грузоподъемность
    int currentFloor; // текущий этаж лифта
    std::vector<int> reachingPoints; // этажи цели, для пассажиров
    char state; // 0 - стоим, 1 - едем вверх, -1 - едем вниз

public:
    TElevator();
    TElevator(int);
    TElevator& operator=(const TElevator&);

    void move(); // использует currentFloor, maxPassengerCount, state, reachingPoints
    void setState(char); // state = s;
    void setReachPoint(int); // reachingPoints.push_back(p);
    void moveToFloor();

signals:
    // Сигнал для отправки информации об изменении этажа
    void floorChanged(int floor);
};

#endif // TELEVATOR_H
