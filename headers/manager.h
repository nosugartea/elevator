#ifndef TMANAGER_H
#define TMANAGER_H

#include <QWidget>
#include <QCloseEvent>
#include <QComboBox>
#include <QLabel>
#include <QLineEdit>
#include "liftButton.h"
#include <vector>

class TManager : public QWidget
{
    Q_OBJECT

    int entrances;
    int floors;
    QComboBox *comboBox;
    QPushButton* startButton;
    QPushButton* callButton;
    QLabel* entrancesLab;
    QLabel* callListLab;
    QLabel* directionLab;
    QLabel* countPassengersLab;
    QLabel* floorDestinLab;
    QLabel* entranceLab;
    QComboBox* callListBox;
    QComboBox* directionBox;
    QComboBox* floorDestinBox;
    QComboBox* entranceBox;
    QLineEdit* countPassengersEdt;

    std::vector<TLiftButton*> buttons;
    std::vector<int> pressedNumbers;
    int activeEntrance;

    int entrance;
    int currFloor;
    int destFloor;


    void showButtons();
    void showMenu();

public:
    TManager(int, int, QWidget *parent = 0);
    ~TManager();

    QPushButton* getStartButton() const {
        return startButton;
    }

    void setNewParam(int, int);
    std::vector<int> getPressedNumbers() { return pressedNumbers; };
    void resetPressedNumbers() { pressedNumbers.clear(); };
    int getActiveEntrance() { return activeEntrance; }
    int getPassengerEntrance();
    int getPassengerCurFloor();
    int getPassengerDestFloor();
    int getPassengerCount();

signals:
    void closed();
    void passengerIsMade();

protected:
    void closeEvent(QCloseEvent*) override;

private slots:
    void handleButtonPressed(int number) {
        if (std::find(pressedNumbers.begin(), pressedNumbers.end(), number) == pressedNumbers.end()) {
            pressedNumbers.push_back(number);
        }
    }

    void resetButtons() {
        for (TLiftButton *button : buttons) {
            button->resetButton();
        }
    }

    void makePassenger();

    void onCallListBoxChanged(int index);
    void onFloorDestinBoxChanged(int index);
    void onEntranceBoxChanged(int index);
};

#endif // TMANAGER_H
