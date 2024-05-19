#include "interface.h"

#include <QMessageBox>

TInterface::TInterface(THouse *h, QWidget *parent)
    : QWidget(parent), house(h)
{
    entrances = h->getEntrancesCount();
    floors = h->getFloorsCount();

    stateSizeX = 150 * (entrances) +10;
    stateSizeY = 50 * (floors + 1) + 20 ;

    setWindowTitle("Лифт мечты");
    setFixedSize(stateSizeX + 430, stateSizeY);

    stateWidget = new TState(entrances, floors, this);
    managerWidget = new TManager(entrances, floors, this);
    paramWidget = new TParam(this);

    stateWidget->setFixedSize(stateSizeX, stateSizeY);
    managerWidget->setFixedSize(stateSizeX + 100, stateSizeY);
    paramWidget->setFixedSize(200, 150);


    connect(managerWidget->getStartButton(), &QPushButton::clicked, this, &TInterface::onStartLift);
    connect(managerWidget->getCallButton(), &QPushButton::clicked, this, &TInterface::onCallLift);
    connect(paramWidget->getSetParamButton(), &QPushButton::clicked, this, &TInterface::onSetParam);
    connect(managerWidget, &TManager::passengerIsMade, this, &TInterface::onPassengerIsMade);
    connect(house, &THouse::passengerIn, this, &TInterface::onPassengerIn);
    connect(house, &THouse::passengerOut, this, &TInterface::onPassengerOut);
    connect(house, &THouse::openDoors, this, &TInterface::onOpenDoors);

    const std::vector<TElevator*>& elevators = house->getElevatorVec();
    for (TElevator* elevator : elevators) {
        connect(elevator, &TElevator::floorChanged, this, &TInterface::onfloorChanged);
    }
}

void TInterface::resizeEvent(QResizeEvent *event)
{
    stateWidget->move(5, 5);
    managerWidget->move(stateSizeX + 10, 5);
    paramWidget->move(stateSizeX + 170, 25);

    QWidget::resizeEvent(event);
}

void TInterface::onPassengerIsMade(int entrance, int currentFloor, int destination, int count, int direction)
{
    if (currentFloor > destination && direction == 1) {
        QMessageBox::warning(this, "Invalid input", "DВведено неправильное направление или этаж назначения.");
        return;
    }
    if (currentFloor < destination && direction == -1) {
        QMessageBox::warning(this, "Invalid input", "UВведено неправильное направление или этаж назначения.");
        return;
    }
    if (count < 0) {
        QMessageBox::warning(this, "Invalid input", "Введено отрицательное количество пассажиров.");
        return;
    }
    if (count == 0) {
        QMessageBox::warning(this, "Warn", "Не задано количество пассажиров.");
        return;
    }

    stateWidget->showPassenger(entrance, destination, currentFloor, count);
    house->setPassenger(entrance, currentFloor, destination, count);
    house->setDirection(entrance, direction);
}

void TInterface::onfloorChanged(int floor) {
    int activeEntrance = managerWidget->getActiveEntrance();
    int capacity = house->getElevatorCapacity(activeEntrance);
    int state = house->getElevatorState(activeEntrance);
    bool doors = house->getElevatorDoors(activeEntrance);
    stateWidget->moveElevator(activeEntrance, floor, capacity, state, doors);
}

void TInterface::onStartLift()
{
    int activeEntrance = managerWidget->getActiveEntrance();
    std::vector<int> goFloors = managerWidget->getPressedNumbers();
    if (goFloors.empty()) return;
    if(house->emptyElevator(activeEntrance)) return;
    managerWidget->resetPressedNumbers();
    house->moveElevator(goFloors, activeEntrance);
}

void TInterface::onCallLift()
{
    int activeEntrance = managerWidget->getPassengerEntrance();
    std::vector<int> goFloors { managerWidget->getPassengerCurFloor() + 1};
    house->moveElevator(goFloors, activeEntrance);
}

void TInterface::onSetParam()
{
    int e = paramWidget->getEntrancesSize();
    int f = paramWidget->getFloorsSize();
    int c = paramWidget->getLiftCapacity();

    if (e < 1) {
        QMessageBox::warning(this, "Invalid input", "Введено отрицательное значение для количества этажей.");
        return;
    } else if (f < 1) {
        QMessageBox::warning(this, "Invalid input", "Введено отрицательное значение для количества подъездов.");
        return;
    } else if (c < 1) {
        QMessageBox::warning(this, "Invalid input", "Введено отрицательное значение для грузоподъемности.");
        return;
    }
    entrances = e;
    floors = f;
    house->resetParam(e, f, c);

    stateSizeX = 150 * (entrances) +10;
    stateSizeY = 50 * (floors + 1) + 20 ;

    setFixedSize(stateSizeX + 430, stateSizeY);

    stateWidget->setFixedSize(stateSizeX, stateSizeY);
    stateWidget->setNewParam(e, f);

    managerWidget->setFixedSize(stateSizeX + 100, stateSizeY);
    managerWidget->setNewParam(e, f);
}

void TInterface::onPassengerIn(int direction, int entrance, int floor)
{
    stateWidget->clearFloor(direction, entrance, floor);
}

void TInterface::onPassengerOut(int entrance)
{
    stateWidget->clearElevator(entrance);
}

void TInterface::onOpenDoors(int entrance)
{
    stateWidget->openDoor(entrance);
}

TInterface::~TInterface()
{
}

