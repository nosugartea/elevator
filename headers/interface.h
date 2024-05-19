#ifndef TINTERFACE_H
#define TINTERFACE_H

#include <QWidget>
#include <QVBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QPainter>

#include "param.h"
#include "state.h"
#include "manager.h"
#include "house.h"

class TInterface : public QWidget
{
    Q_OBJECT

    TState* stateWidget;
    TParam* paramWidget;
    TManager* managerWidget;

    THouse *house;
    QPushButton* startFloor;

    int stateSizeX, stateSizeY;

    int entrances;
    int floors;

signals:
    void closed();

public:
    TInterface(THouse *h, QWidget *parent = nullptr);
    ~TInterface();

protected:
    void closeEvent(QCloseEvent *event) override;
    void resizeEvent(QResizeEvent *event) override;

public slots:
    // Слот для обработки создания пассажира
    void onPassengerIsMade();
    void onfloorChanged(int);
    void onStartLift();
    void onCallLift();
    void onSetParam();
    void onPassengerIn(int, int, int);
    void onPassengerOut(int);
    void onOpenDoors(int);
};
#endif // TINTERFACE_H
