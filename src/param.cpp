#include "param.h"

TParam::TParam(QWidget *parent)
    : QWidget(parent)
{
    setFixedSize(400,400);
}

TParam::~TParam()
{
}

void TParam::closeEvent(QCloseEvent *event)
{
    emit closed();
    QWidget::closeEvent(event);
}
