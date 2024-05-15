#include "interface.h"
#include "house.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    THouse h(2, 9, 4);
    TInterface w(&h);
    w.show();
    return a.exec();
}
