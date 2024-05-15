#include "canvas.h"

TCanvas::TCanvas(QWidget *parent)
    : QWidget(parent)
{
    setFixedSize(400,400);
}

TCanvas::~TCanvas()
{
}

void TCanvas::closeEvent(QCloseEvent *event)
{
    emit closed();
    QWidget::closeEvent(event);
}
