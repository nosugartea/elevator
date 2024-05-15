#ifndef TINTERFACE_H
#define TINTERFACE_H

#include <QWidget>
#include <QLabel>
#include <QLineEdit>
#include <QTextEdit>
#include <QPushButton>
#include <QRadioButton>

class TInterface : public QWidget
{
    Q_OBJECT

    int size_m;

    QLabel *label_size;
    QLineEdit *line_size;
    std::vector<std::vector<QLineEdit*>> matrix_a, matrix_b;
    std::vector<std::vector<QLabel*>> delimeter_m, delimeter_p;

    QPushButton *resize_btn;
    QPushButton *transpose_btn;
    QPushButton *determinant_btn;
    QPushButton *rank_btn;
    QPushButton *print_btn;
    QPushButton *clear_btn;

    QRadioButton *d_mode;
    QRadioButton *c_mode;
    QRadioButton *r_mode;

    QTextEdit *output;

public:
    TInterface(QWidget *parent = nullptr);
    ~TInterface();

public slots:
    void resize();
    void answer(QString msg);
    void clear();

private slots:
    void formRequest();

signals:
    void request(QString);
};
#endif // TINTERFACE_H
