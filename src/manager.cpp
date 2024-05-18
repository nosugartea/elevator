#include "manager.h"

#include <QGridLayout>
#include "MyStyleSheets.h"

TManager::TManager(int e, int f, QWidget *parent)
    : QWidget(parent), entrances(e), floors(f), activeEntrance(0)
{
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

TManager::~TManager()
{
}

void TManager::closeEvent(QCloseEvent *event)
{
    emit closed();
    QWidget::closeEvent(event);
}
void  TManager::setNewParam(int e, int f)
{
    entrances = e;
    floors = f;
    showButtons();
}
