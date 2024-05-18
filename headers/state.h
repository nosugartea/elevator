#ifndef TSTATE_H
#define TSTATE_H

#include <QWidget>
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

public:
    TState(int, int, QWidget *parent = 0);
    ~TState();

    void setNewParam(int, int);
    void moveElevator(int, int, int, int, bool);
    void showPassenger(int, int, int, int);
    void deletePassenger(int, int, int);
    void openDoor(int);

signals:
    void closed();

protected:
    void closeEvent(QCloseEvent*) override;
    void paintEvent(QPaintEvent *event) override;
};

#endif // TSTATE_H
