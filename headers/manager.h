#ifndef TMANAGER_H
#define TMANAGER_H

#include <QWidget>
#include <QCloseEvent>

class TManager : public QWidget
{
    Q_OBJECT

public:
    TManager(QWidget *parent = 0);
    ~TManager();

signals:
    void closed();

protected:
    void closeEvent(QCloseEvent*);
};

#endif // TMANAGER_H
