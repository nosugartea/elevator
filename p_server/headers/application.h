#ifndef APPLICATION_H
#define APPLICATION_H

#include <QObject>
#include <QCoreApplication>

#include "communicator.h"
#include "house.h"

class TApplication : public QCoreApplication
{
    Q_OBJECT

    TCommunicator *comm;

    THouse h;
    struct requestInfo {
        int entrancesCount;
        int floorsCount;
        int maxLiftCapacity;
    };

    void readRequest(int, requestInfo&, QString&);
    void setNewParam(int, int, int);

public:

    TApplication(int, char**);

signals:

public slots:
    void recieve(QByteArray);
};

#endif // APPLICATION_H
