#ifndef TLIFTBUTTON_H
#define TLIFTBUTTON_H

#include <QPushButton>

class TLiftButton : public QPushButton {
    Q_OBJECT

    int number;
    bool isPressed;

public:
    TLiftButton(int number, QWidget *parent = nullptr) : QPushButton(QString::number(number), parent), number(number), isPressed(false) {
        setFixedSize(50, 50);
        setStyleSheet("QPushButton { border-radius: 25px; "
                      "background-color: qlineargradient(x1:0, y1:0, x2:1, y2:1, "
                      "stop:0 rgba(88, 205, 174, 0.3),"
                      "stop:1 rgba(63, 148, 108, 0.3));}");
        connect(this, &QPushButton::clicked, this, &TLiftButton::handleClick);
    }

    int getNumber() const { return number; }

    bool getIsPressed() const { return isPressed; }

    void resetButton() {
        isPressed = false;
        setStyleSheet("QPushButton { border-radius: 25px; "
                      "background-color: qlineargradient(x1:0, y1:0, x2:1, y2:1, "
                      "stop:0 rgba(88, 205, 174, 0.3),"
                      "stop:1 rgba(63, 148, 108, 0.3));}");
    }

signals:
    void buttonPressed(int number);

private slots:
    void handleClick() {
        if (!isPressed) {
            isPressed = true;
            setStyleSheet("QPushButton { border-radius: 25px; "
                          "background-color: qlineargradient(x1:0, y1:0, x2:1, y2:1, "
                          "stop:0 rgba(88, 205, 174, 1),"
                          "stop:1 rgba(63, 148, 108, 1));}");
            emit buttonPressed(number);
        }
    }
};


#endif // TLIFTBUTTON_H
