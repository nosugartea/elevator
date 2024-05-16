#ifndef TINTERFACE_H
#define TINTERFACE_H

#include <QWidget>
#include <QVBoxLayout>
#include <QLabel>
#include <QPainter>

#include "param.h"
#include "house.h"

class TInterface : public QWidget
{
    Q_OBJECT

    TParam param;
    THouse *house;

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
    void onPassengerGenerated(TPassenger *passenger) {
        qDebug() << "Passenger generated: Start Floor" << passenger->getStartFloor()
                 << ", Destination Floor" << passenger->getDestinationFloor();
        // Здесь можно добавить логику для отображения информации о пассажире на интерфейсе
        delete passenger;
    }

    void onLiftMoveT(int floor) {
        qDebug() << "TInterface >> Floor is now: Curr Floor" << floor;
    }

private:
    QLabel *floorLabel;
};
#endif // TINTERFACE_H
