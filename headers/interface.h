#ifndef TINTERFACE_H
#define TINTERFACE_H

#include <QWidget>
#include "param.h"

class TInterface : public QWidget
{
    Q_OBJECT

    TParam param;

signals:
    void closed();

public:
    TInterface(QWidget *parent = nullptr);
    ~TInterface();

protected:
    void closeEvent(QCloseEvent *event);
};
#endif // TINTERFACE_H
