#include "interface.h"

TInterface::TInterface(QWidget *parent)
    : QWidget(parent)
{
    setWindowTitle("Лифт мечты");
    setFixedSize(600, 500);

    canvas.setWindowTitle("Граф");

    connect(this, &TInterface::closed, &canvas, &TCanvas::close);
}

void TInterface::closeEvent(QCloseEvent *event)
{
    emit closed();
    QWidget::closeEvent(event);
}

TInterface::~TInterface()
{
    canvas.close();
}

