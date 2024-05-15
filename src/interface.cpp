#include "interface.h"

TInterface::TInterface(THouse *h, QWidget *parent)
    : QWidget(parent), house(h)
{
    setWindowTitle("Лифт мечты");
    setFixedSize(600, 500);

    param.setWindowTitle("Окно");

    connect(this, &TInterface::closed, &param, &TParam::close);
}

void TInterface::closeEvent(QCloseEvent *event)
{
    emit closed();
    QWidget::closeEvent(event);
}

TInterface::~TInterface()
{
    param.close();
}

