#ifndef MYSTYLESHEETS_H
#define MYSTYLESHEETS_H

const char* comboBoxStyle = R"(
QComboBox:!editable, QComboBox::drop-down:editable { border-radius: 10px;
    background: qlineargradient(x1:0, y1:0, x2:1, y2:0,
                stop:0 rgba(193, 95, 251, 1),
                stop:0.6 rgba(97, 115, 241, 0.7),
                stop:1 rgba(94, 131, 239, 0.7));
}

QComboBox::drop-down {
    border-radius: 10px;
    subcontrol-origin: padding;
    subcontrol-position: top right;
    border-top-right-radius: 12px;
    border-bottom-right-radius: 12px;
    border-top-left-radius: 12px;
    border-bottom-left-radius: 12px;
}

QComboBox QAbstractItemView {
    border-radius: 10px;
    background: qlineargradient(x1:0, y1:0, x2:1, y2:0,
                stop:0 rgba(193, 95, 251, 1),
                stop:0.6 rgba(97, 115, 241, 0.7),
                stop:1 rgba(94, 131, 239, 0.7));
    color: rgb(255, 255, 255);
    border: 1px #FFE5CC;
}
)";

const char* startButtonStyle = R"(
QPushButton {
    border-radius: 25px;
    background-color:   qlineargradient(x1:0, y1:0, x2:1, y2:1,
                        stop:0 rgba(88, 205, 174, 1),
                        stop:1 rgba(63, 148, 108, 1));
}
QPushButton:pressed {
    border-radius: 25px;
    background-color:   qlineargradient(x1:0, y1:0, x2:1, y2:1,
                        stop:0 rgba(88, 205, 174, 0.5),
                        stop:1 rgba(63, 148, 108, 0.5));}
)";

const char* liftButtonStyle = R"(
QPushButton {
    border-radius: 25px;
    background-color: qlineargradient(x1:0, y1:0, x2:1, y2:1,
    stop:0 rgba(88, 205, 174, 0.3),
    stop:1 rgba(63, 148, 108, 0.3));}

QPushButton:checked {
    border-radius: 25px;
    background-color: qlineargradient(x1:0, y1:0, x2:1, y2:1,
    stop:0 rgba(88, 205, 174, 1),
    stop:1 rgba(63, 148, 108, 1));}
)";

#endif // MYSTYLESHEETS_H
