#ifndef TMANAGER_H
#define TMANAGER_H

#include <QWidget>
#include <QCloseEvent>
#include <QComboBox>
#include "liftButton.h"
#include <vector>

class TManager : public QWidget
{
    Q_OBJECT

    int entrances;
    int floors;
    QComboBox *comboBox;
    QPushButton *startButton;
    std::vector<TLiftButton*> buttons;
    std::vector<int> pressedNumbers;
    int activeEntrance;

    void showButtons();

public:
    TManager(int, int, QWidget *parent = 0);
    ~TManager();

    QPushButton* getStartButton() const {
        return startButton;
    }

    void setNewParam(int, int);
    std::vector<int> getPressedNumbers() { return pressedNumbers; };
    void resetPressedNumbers() { pressedNumbers.clear(); };
    int getActiveEntrance() { return activeEntrance; }

signals:
    void closed();

protected:
    void closeEvent(QCloseEvent*) override;

private slots:
    void handleButtonPressed(int number) {
        if (std::find(pressedNumbers.begin(), pressedNumbers.end(), number) == pressedNumbers.end()) {
            pressedNumbers.push_back(number);
        }
    }

    void resetButtons() {
        for (TLiftButton *button : buttons) {
            button->resetButton();
        }
    }
};

#endif // TMANAGER_H
