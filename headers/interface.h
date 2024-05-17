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

    TParam param;
    THouse *house;
    QPushButton* startFloor;
    TState* stateWidget;
    TParam* paramWidget;
    TManager* managerWidget;

signals:
    void closed();

public:
    TInterface(THouse *h, QWidget *parent = nullptr);
    ~TInterface();

protected:
    void closeEvent(QCloseEvent *event) override;
    void paintEvent(QPaintEvent *event) override;

public slots:
    // Слот для обработки создания пассажира
    void onPassengerGenerated(int floor) {
        qDebug() << "Passenger generated: Start Floor" << floor;
    }

    void onfloorChanged(int floor) {
        qDebug() << "TInterface >> Floor is now: Curr Floor" << floor;
    }

    void onStartLift() {
        house->moveElevator(0);
    }
};
#endif // TINTERFACE_H
