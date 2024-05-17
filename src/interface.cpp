#include "interface.h"

TInterface::TInterface(THouse *h, QWidget *parent)
    : QWidget(parent), house(h)
{
    setWindowTitle("Лифт мечты");
    setFixedSize(600, 500);

    param.setWindowTitle("Окно");

    stateWidget = new TState(this);
    paramWidget = new TParam(this);
    managerWidget = new TManager(this);

    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    mainLayout->addWidget(stateWidget);
    mainLayout->addWidget(paramWidget);
    mainLayout->addWidget(managerWidget);
    setLayout(mainLayout);

    //connect(this, &TInterface::closed, &param, &TParam::close);

    startFloor = new QPushButton("Start Floor", this);
    startFloor->setGeometry(140,20,100,25);

    // Подключаем сигналы и слоты
    connect(house, &THouse::passengerGenerated, this, &TInterface::onPassengerGenerated);
    const std::vector<TElevator*>& elevators = house->getElevatorVec();
    for (TElevator* elevator : elevators) {
        connect(elevator, &TElevator::floorChanged, this, &TInterface::onfloorChanged);
    }
    //connect(house, &THouse::passengerGenerated, this, &TInterface::onPassengerGenerated);
    connect(startFloor, &QPushButton::clicked, this, &TInterface::onStartLift);
}

void TInterface::closeEvent(QCloseEvent *event)
{
    emit closed();
    QWidget::closeEvent(event);
}

void TInterface::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    // Определение размеров и положения этажей
    int floorWidth = width() - 20; // ширина этажей
    int floorHeight = 50; // высота этажей
    int numFloors = 5; // количество этажей
    int floorSpacing = 10; // расстояние между этажами

    // Рисование этажей
    for (int i = 0; i < numFloors; ++i) {
        int x = 10; // начальная позиция по x
        int y = i * (floorHeight + floorSpacing) + 10; // позиция этажа по y
        painter.fillRect(x, y, floorWidth, floorHeight, Qt::green);
        painter.drawText(x + 5, y + floorHeight / 2, QString("Floor %1").arg(i + 1));
    }
}

TInterface::~TInterface()
{
    param.close();
}

