#ifndef VIEWER_H
#define VIEWER_H

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

#endif // VIEWER_H
