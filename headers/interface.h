#ifndef TINTERFACE_H
#define TINTERFACE_H

#include <QWidget>
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
    void closeEvent(QCloseEvent *event);
};
#endif // TINTERFACE_H
