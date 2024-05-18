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
    paramWidget = new TParam(this);
    managerWidget = new TManager(entrances, floors, this);

    stateWidget->setFixedSize(stateSizeX, stateSizeY);
    paramWidget->setFixedSize(200, stateSizeY);
    managerWidget->setFixedSize(430, stateSizeY);

    connect(managerWidget->getStartButton(), &QPushButton::clicked, this, &TInterface::onStartLift);
    connect(paramWidget->getSetParamButton(), &QPushButton::clicked, this, &TInterface::onSetParam);
    connect(managerWidget, &TManager::passengerIsMade, this, &TInterface::onPassengerIsMade);
    connect(house, &THouse::passengerIn, this, &TInterface::onPassengerIn);
     connect(house, &THouse::openDoors, this, &TInterface::onOpenDoors);

    const std::vector<TElevator*>& elevators = house->getElevatorVec();
    for (TElevator* elevator : elevators) {
        connect(elevator, &TElevator::floorChanged, this, &TInterface::onfloorChanged);
    }
}

void TInterface::closeEvent(QCloseEvent *event)
{
    emit closed();
    QWidget::closeEvent(event);
}

void TInterface::resizeEvent(QResizeEvent *event)
{
    stateWidget->move(5, 5);
    paramWidget->move(stateSizeX + 170, 25);
    managerWidget->move(stateSizeX + 10, 5);

    QWidget::resizeEvent(event);
}

void TInterface::onPassengerIsMade()
{
    int entrance = managerWidget->getPassengerEntrance() - 1;
    int destination =  managerWidget->getPassengerDestFloor() - 1;
    int floor = managerWidget->getPassengerCurFloor() - 1;
    int count = managerWidget->getPassengerCount();
    stateWidget->showPassenger(entrance, destination, floor, count);
}

void TInterface::onfloorChanged(int floor) {
    int activeEntrance = managerWidget->getActiveEntrance();
    int capacity = house->getElevatorCapacity(activeEntrance);
    int state = house->getElevatorState(activeEntrance);
    bool doors = house->getElevatorDoors(activeEntrance);
    stateWidget->moveElevator(activeEntrance, floor, capacity, state, doors);
}

void TInterface::onStartLift() {
    std::vector<int> goFloors = managerWidget->getPressedNumbers();
    if (goFloors.empty()) return;
    managerWidget->resetPressedNumbers();
    int activeEntrance = managerWidget->getActiveEntrance();
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

    setFixedSize(stateSizeX + 600, stateSizeY);
    stateWidget->setFixedSize(stateSizeX, stateSizeY);
    paramWidget->setFixedSize(200, stateSizeY);
    managerWidget->setFixedSize(200, stateSizeY);
    stateWidget->setNewParam(e, f);
    managerWidget->setNewParam(e, f);
}

void TInterface::onPassengerIn(int direction, int entrance, int floor)
{
    stateWidget->deletePassenger(direction, entrance, floor);
}

void TInterface::onOpenDoors(int entrance)
{
    stateWidget->openDoor(entrance);
}

TInterface::~TInterface()
{
}

