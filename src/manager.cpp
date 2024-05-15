#include "manager.h"

TManager::TManager(QWidget *parent)
    : QWidget(parent)
{
    setFixedSize(400,400);
}

TManager::~TManager()
{
}

void TManager::closeEvent(QCloseEvent *event)
{
    emit closed();
    QWidget::closeEvent(event);
}
