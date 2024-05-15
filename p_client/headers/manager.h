#ifndef VIEWER_H
#define VIEWER_H

#include <QWidget>
#include <QCloseEvent>

class TCanvas : public QWidget
{
    Q_OBJECT

public:
    TCanvas(QWidget *parent = 0);
    ~TCanvas();

signals:
    void closed();

protected:
    void closeEvent(QCloseEvent*);
};

#endif // VIEWER_H
