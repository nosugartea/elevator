#include "manager.h"

#include <QGridLayout>
#include "myStyleSheets.h"

TManager::TManager(int e, int f, QWidget *parent) : QWidget(parent),
    entrances(e),
    floors(f),
    activeEntrance(0),
    passengerCurrFloor(0),
    passengerDestFloor(0),
    passengerDirection(1)
{
    comboBox = new QComboBox(this);
    comboBox->setStyleSheet(comboBoxStyle1);
    comboBox->setFixedSize(110, 50);
    comboBox->move(0, 0);

    QObject::connect(comboBox, QOverload<int>::of(&QComboBox::currentIndexChanged), this,
                     [&](int index){ activeEntrance = index; });

    startButton = new QPushButton("Начать", this);
    startButton->setFixedSize(50, 50);
    startButton->setStyleSheet(startButtonStyle);

    callButton = new QPushButton("Вызвать", this);
    callButton->setStyleSheet(buttonStyle);

    callListLab = new QLabel("Вызвать на этаже", this);
    directionLab = new QLabel("Направление", this);
    countPassengersLab = new QLabel("Количество пассажиров", this);
    floorDestinLab = new QLabel("Этаж назначения", this);

    callListBox = new QComboBox(this);
    floorDestinBox = new QComboBox(this);
    directionBox = new QComboBox(this);

    countPassengersEdt = new QLineEdit(this);

    connect(callButton, &QPushButton::clicked, this, &TManager::onMakePassenger);
    connect(callListBox, QOverload<int>::of(&QComboBox::currentIndexChanged), this, &TManager::onCallListBoxChanged);
    connect(floorDestinBox, QOverload<int>::of(&QComboBox::currentIndexChanged), this, &TManager::onFloorDestinBoxChanged);
    connect(directionBox, QOverload<int>::of(&QComboBox::currentIndexChanged), this, &TManager::onDirectionBoxChanged);

    showMenu();
    showButtons();
}

TManager::~TManager()
{
    delete comboBox;
    delete startButton;
    delete callButton;
    delete entrancesLab;
    delete callListLab;
    delete directionLab;
    delete countPassengersLab;
    delete floorDestinLab;
    delete callListBox;
    delete directionBox;
    delete floorDestinBox;
    delete countPassengersEdt;

    for (TLiftButton* button : buttons) {
        delete button;
    }
    buttons.clear();
}

void TManager::showButtons()
{
    int numRows = floors / 2 + floors % 2;
    int numCols = 2;

    int buttonSize = 50;
    int buttonSpacing = 10;
    int startX = 0;
    int startY = 60;

    for (int i = 0; i < entrances; ++i) {
        comboBox->addItem("Подъезд " + QString::number(i+1));
    }

    startButton->move(startX + (buttonSize + buttonSpacing)/2, numRows * (buttonSize + buttonSpacing) + startY);

    if (!buttons.empty()) {
        for (TLiftButton* button : buttons) {
            delete button;
        }
        buttons.clear();
    }

    for (int i = 0; i < numRows; ++i) {
        for (int j = 0; j < numCols; ++j) {
            int number = i * numCols + j + 1;
            if (number > floors) return;
            TLiftButton *button = new TLiftButton(number, this);
            button->move(startX + j * (buttonSize + buttonSpacing), startY + i * (buttonSize + buttonSpacing));
            connect(button, &TLiftButton::buttonPressed, this, &TManager::onStartButtonPressed);
            buttons.push_back(button);
            button->show();
        }
    }
}

void TManager::showMenu()
{
    int startX = 150;
    int startY = 140;
    int spacingY = 30;
    int spacingX = 160;
    int width = 70;
    int widthLab = 150;
    int height = 25;

    callButton->setGeometry(startX + 60, startY + 5 * spacingY, width, height);

    callListLab->setGeometry(startX, startY + spacingY, widthLab, height);
    directionLab->setGeometry(startX, startY + 2 * spacingY, widthLab, height);
    countPassengersLab->setGeometry(startX, startY + 3 * spacingY, widthLab, height);
    floorDestinLab->setGeometry(startX, startY + 4 * spacingY, widthLab, height);

    callListBox->setGeometry(startX + spacingX, startY + spacingY, width, height);
    floorDestinBox->setGeometry(startX + spacingX, startY + 4 * spacingY, width, height);
    directionBox->setGeometry(startX + spacingX, startY + 2 * spacingY, width, height);

    countPassengersEdt->setGeometry(startX + spacingX, startY + 3 * spacingY, width, height);

    for (int i = 0; i < floors; ++i) {
        callListBox->addItem(QString::number(i + 1));
        floorDestinBox->addItem(QString::number(i + 1));
    }

    directionBox->addItem("Up");
    directionBox->addItem("Down");
}

QPushButton* TManager::getStartButton() const
{
    return startButton;
}

QPushButton* TManager::getCallButton() const
{
    return callButton;
}

void TManager::setNewParam(int e, int f)
{

    comboBox->clear();
    callListBox->clear();
    floorDestinBox->clear();
    directionBox->clear();

    entrances = e;
    floors = f;
    showMenu();
    showButtons();
}

void TManager::resetPressedNumbers()
{
    pressedNumbers.clear();
}

std::vector<int> TManager::getPressedNumbers()
{
    return pressedNumbers;
}

int TManager::getActiveEntrance()
{
    return activeEntrance;
}

int TManager::getPassengerEntrance()
{
    return activeEntrance;
}

int TManager::getPassengerCurFloor()
{
    return  passengerCurrFloor;
}

void TManager::onStartButtonPressed(int number)
{
    if (std::find(pressedNumbers.begin(), pressedNumbers.end(), number) == pressedNumbers.end()) {
        pressedNumbers.push_back(number);
    }
}

void TManager::resetButtons(int id)
{
    buttons[id]->resetButton();
}

void TManager::onMakePassenger()
{
    emit passengerIsMade(activeEntrance, passengerCurrFloor, passengerDestFloor, countPassengersEdt->text().toInt(), passengerDirection);
}

void TManager::onCallListBoxChanged(int index)
{
    passengerCurrFloor = index;
}

void TManager::onFloorDestinBoxChanged(int index)
{
    passengerDestFloor = index;
}

void TManager::onDirectionBoxChanged(int index)
{
    if (index == 0) {
        passengerDirection = 1;
    }
    if (index == 1) {
        passengerDirection = -1;
    }
}
