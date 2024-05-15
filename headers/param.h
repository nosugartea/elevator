#ifndef TPARAM_H
#define TPARAM_H

#include <QWidget>
#include <QCloseEvent>

class TParam : public QWidget
{
    Q_OBJECT

public:
    TParam(QWidget *parent = 0);
    ~TParam();

signals:
    void closed();

protected:
    void closeEvent(QCloseEvent*);
};

#endif // TPARAM_H
