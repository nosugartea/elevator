#include "interface.h"

TInterface::TInterface(QWidget *parent)
    : QWidget(parent)
{
    setWindowTitle("Лифт мечты");
    setFixedSize(600, 500);

    param.setWindowTitle("Граф");

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

