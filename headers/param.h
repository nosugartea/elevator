#ifndef TPARAM_H
#define TPARAM_H

#include <QWidget>
#include <QCloseEvent>
#include <QPushButton>
#include <QLabel>
#include <QLineEdit>

class TParam : public QWidget
{
    Q_OBJECT

    QLabel* floorsSizeLab;
    QLabel* entrancesSizeLab;
    QLabel* liftCapacityLab;

    QLineEdit* floorsSizeEdt;
    QLineEdit* entrancesSizeEdt;
    QLineEdit* liftCapacityEdt;

    QPushButton* setParameters;

public:
    TParam(QWidget *parent = 0);
    ~TParam();

    QPushButton* getSetParamButton() const {
        return setParameters;
    }
    int getFloorsSize();
    int getEntrancesSize();
    int getLiftCapacity();

signals:
    void closed();

protected:
    void closeEvent(QCloseEvent*);
};

#endif // TPARAM_H
