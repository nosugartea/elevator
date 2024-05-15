#include "interface.h"
#include "common.h"

TInterface::TInterface(QWidget *parent)
    : QWidget(parent)
{
    setWindowTitle("Работа №6");
    setFixedSize(800, 650);

    // for enter matrix size
    label_size = new QLabel("matrix size = ", this);
    label_size->setGeometry(40,20,100,25);
    line_size = new QLineEdit("2", this);
    line_size->setGeometry(140,20,30,25);

    // buttons
    resize_btn = new QPushButton("Задать размер", this);
    resize_btn->setGeometry(420, 10, 150, 60);

    transpose_btn = new QPushButton("Транспонировать", this);
    transpose_btn->setGeometry(40, 360, 150, 60);

    determinant_btn = new QPushButton("Найти определитель", this);
    determinant_btn->setGeometry(230, 360, 150, 60);

    rank_btn = new QPushButton("Найти ранг", this);
    rank_btn->setGeometry(420, 360, 150, 60);

    print_btn = new QPushButton("Вывести", this);
    print_btn->setGeometry(610, 360, 150, 60);

    clear_btn = new QPushButton("Очистить поля", this);
    clear_btn->setGeometry(610, 10, 150, 60);

    d_mode = new QRadioButton("Вещественные числа", this);
    d_mode->setGeometry(40, 600, 150, 20);
    c_mode = new QRadioButton("Комплексные числа", this);
    c_mode->setGeometry(230, 600, 150, 20);
    r_mode = new QRadioButton("Рациональные числа", this);
    r_mode->setGeometry(420, 600, 150, 20);
    d_mode->setChecked(true);

    output = new QTextEdit("", this);
    output->setGeometry(40, 430, 720, 150);

    size_m = 2;
    resize();

    // slots
    connect(resize_btn, SIGNAL(pressed()), this, SLOT(resize()));
    connect(transpose_btn, SIGNAL(pressed()), this, SLOT(formRequest()));
    connect(determinant_btn, SIGNAL(pressed()), this, SLOT(formRequest()));
    connect(rank_btn, SIGNAL(pressed()), this, SLOT(formRequest()));
    connect(print_btn, SIGNAL(pressed()), this, SLOT(formRequest()));
    connect(clear_btn, SIGNAL(pressed()), this, SLOT(clear()));
    connect(d_mode, SIGNAL(toggled(bool)), this, SLOT(resize()));
    connect(c_mode, SIGNAL(toggled(bool)), this, SLOT(resize()));
    connect(r_mode, SIGNAL(toggled(bool)), this, SLOT(resize()));
}

void TInterface::resize()
{
    if (!matrix_a.empty() && !matrix_b.empty() && !delimeter_m.empty() && !delimeter_p.empty()) {
        for (int i = 0; i < size_m; ++i) {
            for (int j = 0; j < size_m; ++j) {
                delete matrix_a[i][j];
                delete matrix_b[i][j];
                delete delimeter_m[i][j];
                delete delimeter_p[i][j];
            }
        }
        matrix_a.clear();
        matrix_b.clear();
        delimeter_m.clear();
        delimeter_p.clear();
    }

    if (!line_size->text().isNull()) {
        size_m = line_size->text().toInt();
    }

    matrix_a.resize(size_m);
    matrix_b.resize(size_m);
    delimeter_m.resize(size_m);
    delimeter_p.resize(size_m);
    for (int i = 0; i < size_m; ++i) {
        matrix_a[i].resize(size_m);
        matrix_b[i].resize(size_m);
        delimeter_m[i].resize(size_m);
        delimeter_p[i].resize(size_m);
        for (int j = 0; j < size_m; ++j) {
            if (d_mode->isChecked())
            {
                matrix_a[i][j] = new QLineEdit("0", this);
                matrix_a[i][j]->setGeometry(40 + i * 110, 80 + j * 40, 30, 25);
                matrix_a[i][j]->show();
            }

            if (c_mode->isChecked())
            {
                matrix_a[i][j] = new QLineEdit("0", this);
                matrix_a[i][j]->setGeometry(40 + i * 110, 80 + j * 40, 30, 25);
                matrix_a[i][j]->show();

                delimeter_m[i][j] = new QLabel(" +", this);
                delimeter_m[i][j]->setGeometry(70 + i * 110, 80 + j * 40, 10, 25);
                delimeter_m[i][j]->show();

                matrix_b[i][j] = new QLineEdit("0", this);
                matrix_b[i][j]->setGeometry(85 + i * 110, 80 + j * 40, 30, 25);
                matrix_b[i][j]->show();

                delimeter_p[i][j] = new QLabel(" i", this);
                delimeter_p[i][j]->setGeometry(115 + i * 110, 80 + j * 40, 10, 25);
                delimeter_p[i][j]->show();
            }

            if (r_mode->isChecked())
            {
                matrix_a[i][j] = new QLineEdit("0", this);
                matrix_a[i][j]->setGeometry(40 + i * 110, 80 + j * 40, 30, 25);
                matrix_a[i][j]->show();

                delimeter_m[i][j] = new QLabel(" /", this);
                delimeter_m[i][j]->setGeometry(70 + i * 110, 80 + j * 40, 10, 25);
                delimeter_m[i][j]->show();

                matrix_b[i][j] = new QLineEdit("1", this);
                matrix_b[i][j]->setGeometry(80 + i * 110, 80 + j * 40, 30, 25);
                matrix_b[i][j]->show();
            }
        }
    }
}

void TInterface::answer(QString msg)
{
    QString text;
    int p = msg.indexOf(separator);
    int t = msg.left(p).toInt();
    msg = msg.mid(p+1,msg.length()-p-1);
    switch (t)
    {
    case TRANSPOSE_ANSWER:
        text = "Transposed:\n";
        text += msg;
        output->clear();
        output->setText(text);
        break;
    case DETERMINANT_ANSWER:
        text = "Determinant is: ";
        text += msg;
        output->clear();
        output->setText(text);
        break;
    case RANK_ANSWER:
        text = "Rank is: ";
        text += msg;
        output->clear();
        output->setText(text);
        break;
    case PRINT_ANSWER:
        text = "Your matrix is:\n";
        text += msg;
        output->setText(text);
        break;
    default: break;
    }
}

void TInterface::formRequest()
{
    QString msg;
    msg << QString::number(size_m);

    if (d_mode->isChecked())
    {
        msg << QString().setNum(D_MODE);
        for (int i = 0; i < size_m; ++i) {
            for (int j = 0; j < size_m; ++j) {
                msg << matrix_a[i][j]->text();
            }
        }
    }
    if (c_mode->isChecked())
    {
        msg << QString().setNum(C_MODE);
        for (int i = 0; i < size_m; ++i) {
            for (int j = 0; j < size_m; ++j) {
                msg << matrix_a[i][j]->text() << matrix_b[i][j]->text();
            }
        }
    }

    if (r_mode->isChecked())
    {
        msg << QString().setNum(R_MODE);
        for (int i = 0; i < size_m; ++i) {
            for (int j = 0; j < size_m; ++j) {
                msg << matrix_a[i][j]->text() << matrix_b[i][j]->text();
            }
        }
    }

    QPushButton *btn = (QPushButton*)sender();
    if (btn == transpose_btn)
    {
        msg << QString().setNum(TRANSPOSE_REQUEST);
    }
    if (btn == determinant_btn)
        msg << QString().setNum(DETERMINANT_REQUEST);
    if (btn == rank_btn)
    {
        msg << QString().setNum(RANK_REQUEST);
    }
    if (btn == print_btn)
    {
        msg << QString().setNum(PRINT_REQUEST);
    }
    emit request(msg);
}

void TInterface::clear()
{
    for (int i = 0; i < size_m; ++i) {
        for (int j = 0; j < size_m; ++j) {

            if (d_mode->isChecked())
            {
                matrix_a[i][j]->clear();
                matrix_a[i][j]->setText("0");
            }

            if (c_mode->isChecked())
            {
                matrix_a[i][j]->clear();
                matrix_a[i][j]->setText("0");

                matrix_b[i][j]->clear();
                matrix_b[i][j]->setText("0");
            }

            if (r_mode->isChecked())
            {
                matrix_a[i][j]->clear();
                matrix_a[i][j]->setText("0");

                matrix_b[i][j]->clear();
                matrix_b[i][j]->setText("1");
            }
        }
    }
}

TInterface::~TInterface()
{
    delete label_size;
    delete line_size;
    delete resize_btn;
    delete transpose_btn;
    delete determinant_btn;
    delete rank_btn;
    delete print_btn;
    delete clear_btn;
    delete d_mode;
    delete c_mode;
    delete r_mode;
    delete output;

    for (int i = 0; i < size_m; ++i) {
        for (int j = 0; j < size_m; ++j) {
            delete matrix_a[i][j];
            delete matrix_b[i][j];
            delete delimeter_m[i][j];
            delete delimeter_p[i][j];
        }
    }
    for (int i = 0; i < size_m; ++i) {
        matrix_a[i].clear();
        matrix_b[i].clear();
        delimeter_m[i].clear();
        delimeter_p[i].clear();
    }
    matrix_a.clear();
    matrix_b.clear();
    delimeter_m.clear();
    delimeter_p.clear();
}

