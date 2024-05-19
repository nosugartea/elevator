#include "param.h"

#include <QMessageBox>

TParam::TParam(QWidget *parent)
    : QWidget(parent)
{
    entrancesSizeLab = new QLabel("Подъезды: ", this);
    entrancesSizeLab->setGeometry(0,25,100,25);
    floorsSizeLab = new QLabel("Этажи: ", this);
    floorsSizeLab->setGeometry(0,50,100,25);
    liftCapacityLab = new QLabel("Грузоподъемность: ", this);
    liftCapacityLab->setGeometry(0,75,130,25);

    entrancesSizeEdt = new QLineEdit("2", this);
    entrancesSizeEdt->setGeometry(140,25,25,25);
    floorsSizeEdt = new QLineEdit("9", this);
    floorsSizeEdt->setGeometry(140,50,25,25);
    liftCapacityEdt = new QLineEdit("4", this);
    liftCapacityEdt->setGeometry(140,75,25,25);

    setParameters = new QPushButton("Изменить", this);
    setParameters->setGeometry(35,110,100,25);
}

TParam::~TParam()
{
}

QPushButton* TParam::getSetParamButton() const
{
    return setParameters;
}

int TParam::getFloorsSize()
{
    bool ok;
    int num = floorsSizeEdt->text().toInt(&ok);
    if (ok) {
        return num;
    } else {
        QMessageBox::warning(this, "Conversion Error", "Введено нечисловое значение для количества этажей.");
    }
    return -1;
}

int TParam::getEntrancesSize()
{
    bool ok;
    int num = entrancesSizeEdt->text().toInt(&ok);
    if (ok) {
        return num;
    } else {
        QMessageBox::warning(this, "Conversion Error", "Введено нечисловое значение для количества подъездов.");
    }
    return -1;
}

int TParam::getLiftCapacity()
{
    bool ok;
    int num = liftCapacityEdt->text().toInt(&ok);
    if (ok) {
        return num;
    } else {
        QMessageBox::warning(this, "Conversion Error", "Введено нечисловое значение для грузоподъемности.");
    }
    return -1;
}
