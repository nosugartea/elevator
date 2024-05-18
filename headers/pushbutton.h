#ifndef TPUSHBUTTON_H
#define TPUSHBUTTON_H

#include <QPushButton>

class TPushButton : public QPushButton {
    Q_OBJECT

    bool isPressed;

public:
    TPushButton(QString t, QWidget *parent = nullptr) : QPushButton(t, parent), isPressed(false) {
        setFixedSize(50, 50);
        setStyleSheet("QPushButton { border-radius: 25px; background-color: lightgray; }");
        connect(this, &QPushButton::clicked, this, &TPushButton::handleClick);
    }

    bool getIsPressed() const { return isPressed; }

    void resetButton() {
        isPressed = false;
        setStyleSheet("QPushButton { border-radius: 25px; background-color: lightgray; }");
    }

signals:
    void buttonPressed();

private slots:
    void handleClick() {
        if (!isPressed) {
            isPressed = true;
            setStyleSheet("QPushButton { border-radius: 25px; background-color: qlineargradient(x1:0, y1:0, x2:1, y2:1,"
                          "stop:0 rgba(88, 205, 174, 0.5),"
                          "stop:1 rgba(63, 148, 108, 0.5));}");
            emit buttonPressed();
        }
    }
};

#endif // TPUSHBUTTON_H
