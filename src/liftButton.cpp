#include "liftButton.h"

TLiftButton::TLiftButton(int number, QWidget *parent) :
    QPushButton(QString::number(number), parent),
    number(number),
    isPressed(false)
{
    setFixedSize(50, 50);
    setStyleSheet("QPushButton { border-radius: 25px; "
                  "background-color: qlineargradient(x1:0, y1:0, x2:1, y2:1, "
                  "stop:0 rgba(88, 205, 174, 0.3),"
                  "stop:1 rgba(63, 148, 108, 0.3));}");
    connect(this, &QPushButton::clicked, this, &TLiftButton::handleClick);
}

int TLiftButton::getNumber() const
{
    return number;
}

bool TLiftButton::getIsPressed() const
{
    return isPressed;
}

void TLiftButton::resetButton()
{
    isPressed = false;
    setStyleSheet("QPushButton { border-radius: 25px; "
                  "background-color: qlineargradient(x1:0, y1:0, x2:1, y2:1, "
                  "stop:0 rgba(88, 205, 174, 0.3),"
                  "stop:1 rgba(63, 148, 108, 0.3));}");
}

void TLiftButton::handleClick() {
    if (!isPressed) {
        isPressed = true;
        setStyleSheet("QPushButton { border-radius: 25px; "
                      "background-color: qlineargradient(x1:0, y1:0, x2:1, y2:1, "
                      "stop:0 rgba(88, 205, 174, 1),"
                      "stop:1 rgba(63, 148, 108, 1));}");
        emit buttonPressed(number);
    }
}
