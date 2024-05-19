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

    int passengerEntrance;
    int passengerCurrFloor;
    int passengerDestFloor;
    int passengerDirection;


    void showButtons();
    void showMenu();

public:
    TManager(int, int, QWidget *parent = 0);
    ~TManager();

    QPushButton* getStartButton() const;
    QPushButton* getCallButton() const;

    void resetPressedNumbers(); //
    void setNewParam(int, int);
    std::vector<int> getPressedNumbers();
    int getActiveEntrance();
    int getPassengerEntrance();
    int getPassengerCurFloor();


signals:
    void passengerIsMade(int, int, int, int, int);

private slots:
    void onStartButtonPressed(int number);
    void onResetButtons(); //
    void onMakePassenger();
    void onCallListBoxChanged(int index);
    void onFloorDestinBoxChanged(int index);
    void onEntranceBoxChanged(int index);
    void onDirectionBoxChanged(int index);
};

#endif // TMANAGER_H
