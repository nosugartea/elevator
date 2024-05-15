#include "state.h"

TState::TState(QWidget *parent)
    : QWidget(parent)
{
    setFixedSize(400,400);
}

TState::~TState()
{
}

void TState::closeEvent(QCloseEvent *event)
{
    emit closed();
    QWidget::closeEvent(event);
}
