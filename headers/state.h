#ifndef TSTATE_H
#define TSTATE_H

#include <QWidget>
#include <QCloseEvent>

class TState : public QWidget
{
    Q_OBJECT

public:
    TState(QWidget *parent = 0);
    ~TState();

signals:
    void closed();

protected:
    void closeEvent(QCloseEvent*);
};

#endif // TSTATE_H
