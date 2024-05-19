#ifndef TLIFTBUTTON_H
#define TLIFTBUTTON_H

#include <QPushButton>

class TLiftButton : public QPushButton {
    Q_OBJECT

    int number;
    bool isPressed;

public:
    TLiftButton(int number, QWidget *parent = nullptr);
    int getNumber() const;
    bool getIsPressed() const;
    void resetButton();

signals:
    void buttonPressed(int number);

private slots:
    void handleClick();
};


#endif // TLIFTBUTTON_H
