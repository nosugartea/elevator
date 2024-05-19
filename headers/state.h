#ifndef TSTATE_H
#define TSTATE_H

#include <QWidget>
#include <QTextEdit>
#include <QCloseEvent>
#include <vector>

class TState : public QWidget
{
    Q_OBJECT

    int entrances;
    int floors;
    std::vector<int> elevatorsState;
    std::vector<bool> elevatorsDoors;
    std::vector<int> elevatorsPosition;
    std::vector<int> elevatorsPassengersIn;
    std::vector<std::vector<int>> passengerUP;
    std::vector<std::vector<int>> passengerDOWN;
    QTextEdit* passengerInfo;

public:
    TState(int, int, QWidget *parent = 0);
    ~TState();

    void showPassenger(int entrance, int dest, int appear, int count);
    void setNewParam(int, int);
    void moveElevator(int, int, int, int, bool);
    void clearFloor(int, int, int);
    void clearElevator(int);
    void openDoor(int); 

protected:
    void paintEvent(QPaintEvent *event) override;
};

#endif // TSTATE_H
