#ifndef TINTERFACE_H
#define TINTERFACE_H

#include <QWidget>
#include "canvas.h"

class TInterface : public QWidget
{
    Q_OBJECT

    TCanvas canvas;

signals:
    void closed();

public:
    TInterface(QWidget *parent = nullptr);
    ~TInterface();

protected:
    void closeEvent(QCloseEvent *event);
};
#endif // TINTERFACE_H
