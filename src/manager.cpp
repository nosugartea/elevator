#include "manager.h"

#include <QGridLayout>
#include "myStyleSheets.h"

TManager::TManager(int e, int f, QWidget *parent)
    : QWidget(parent), entrances(e), floors(f), activeEntrance(0)
{
    entrance = 0;
    currFloor = 1;
    destFloor = 1;
    direction = 1;

    comboBox = new QComboBox(this);
    for (int i = 0; i < entrances; ++i) {
        comboBox->addItem("Подъезд " + QString::number(i+1));
    }

    comboBox->setStyleSheet(comboBoxStyle);
    comboBox->setFixedSize(110, 50);
    comboBox->move(0, 0);

    QObject::connect(comboBox, QOverload<int>::of(&QComboBox::currentIndexChanged),
                     [&](int index){ activeEntrance = index; });

    startButton = new QPushButton("Начать", this);
    startButton->setFixedSize(50, 50);
    startButton->setStyleSheet(startButtonStyle);
    connect(startButton, &QPushButton::clicked, this, &TManager::resetButtons);

    showMenu();
    showButtons();
}

void TManager::showButtons()
{
    int numRows = floors / 2 + floors % 2;
    int numCols = 2;

    int buttonSize = 50;
    int buttonSpacing = 10;
    int startX = 0;
    int startY = 60;

    startButton->move(startX+(buttonSize + buttonSpacing)/2,numRows * (buttonSize + buttonSpacing) + startY);

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
            connect(button, &TLiftButton::buttonPressed, this, &TManager::handleButtonPressed);
            buttons.push_back(button);
        }
    }
}

void TManager::showMenu()
{
    int startX = 150;
    int startY = 200;
    int spacingY = 30;
    int spacingX = 160;
    int width = 70;
    int widthLab = 150;
    int height = 25;

    callButton = new QPushButton("Вызвать", this);
    callButton->setGeometry(startX, startY + 5 * spacingY, width, height);
    connect(callButton, &QPushButton::clicked, this, &TManager::makePassenger);

    entranceLab = new QLabel("Подъезд", this);
    entranceLab->setGeometry(startX, startY, widthLab, height);

    callListLab = new QLabel("Вызвать на этаже", this);
    callListLab->setGeometry(startX, startY + spacingY, widthLab, height);

    directionLab = new QLabel("Направление", this);
    directionLab->setGeometry(startX, startY + 2 * spacingY, widthLab, height);

    countPassengersLab = new QLabel("Количество пассажиров", this);
    countPassengersLab->setGeometry(startX, startY + 3 * spacingY, widthLab, height);

    floorDestinLab = new QLabel("Этаж назначения", this);
    floorDestinLab->setGeometry(startX, startY + 4 * spacingY, widthLab, height);

    callListBox = new QComboBox(this);
    callListBox->setGeometry(startX + spacingX, startY + spacingY, width, height);
    floorDestinBox = new QComboBox(this);
    floorDestinBox->setGeometry(startX + spacingX, startY + 4 * spacingY, width, height);
    for (int j = 0; j < floors; ++j) {
        callListBox->addItem(QString::number(j + 1));
        floorDestinBox->addItem(QString::number(j + 1));
    }

    directionBox = new QComboBox(this);
    directionBox->setGeometry(startX + spacingX, startY + 2 * spacingY, width, height);
    directionBox->addItem("Up");
    directionBox->addItem("Down");

    entranceBox = new QComboBox(this);
    for (int j = 0; j < entrances; ++j) {
        entranceBox->addItem(QString::number(j + 1));
    }
    entranceBox->setGeometry(startX + spacingX, startY, width, height);

    countPassengersEdt = new QLineEdit(this);
    countPassengersEdt->setGeometry(startX + spacingX, startY + 3 * spacingY, width, height);

    connect(entranceBox, QOverload<int>::of(&QComboBox::currentIndexChanged), this, &TManager::onEntranceBoxChanged);
    connect(callListBox, QOverload<int>::of(&QComboBox::currentIndexChanged), this, &TManager::onCallListBoxChanged);
    connect(floorDestinBox, QOverload<int>::of(&QComboBox::currentIndexChanged), this, &TManager::onFloorDestinBoxChanged);
    connect(directionBox, QOverload<int>::of(&QComboBox::currentIndexChanged), this, &TManager::onDirectionBoxChanged);
}

TManager::~TManager()
{
}

void TManager::closeEvent(QCloseEvent *event)
{
    emit closed();
    QWidget::closeEvent(event);
}
void TManager::setNewParam(int e, int f)
{
    entrances = e;
    floors = f;
    showMenu();
    showButtons();
}

void TManager::makePassenger()
{
    emit passengerIsMade();
}

int TManager::getPassengerEntrance()
{
    return entrance;
}

int TManager::getPassengerCurFloor()
{
    return currFloor;
}

int TManager::getPassengerDestFloor()
{
    return destFloor;
}

int TManager::getDirection()
{
    return direction;
}

int TManager::getPassengerCount()
{
    return countPassengersEdt->text().toInt();
}

void TManager::onCallListBoxChanged(int index)
{
    currFloor = index;
}

void TManager::onFloorDestinBoxChanged(int index)
{
    destFloor = index;
}

void TManager::onEntranceBoxChanged(int index)
{
    entrance = index;
}

void TManager::onDirectionBoxChanged(int index)
{
    direction = index - 1;
}
