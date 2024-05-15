#include "application.h"
#include "common.h"

TServer::TServer(QObject *parent) : QObject(parent)
{
    TCommParams pars = { QHostAddress("127.0.0.1"), 10000,
                        QHostAddress("127.0.0.1"), 10001};
    comm = new TCommunicator(pars, this);

    connect(comm, SIGNAL(recieved(QByteArray)), this, SLOT(recieve(QByteArray)));
}

void TApplication::recieve(QByteArray msg)
{
    QString answer;
    int pos = msg.indexOf(separator.toLatin1());
    int mode = msg.left(pos).toInt();
    msg = msg.right(msg.length()-pos-1);

    requestInfo info;
    if (mode == D_MODE) { // set param
        pos = msg.indexOf(separator.toLatin1());
        info.entrancesCount = msg.left(pos).toInt();

        pos = msg.indexOf(separator.toLatin1());
        info.floorsCount = msg.left(pos).toInt();

        pos = msg.indexOf(separator.toLatin1());
        info.maxLiftCapacity = msg.left(pos).toInt();

        pos = msg.indexOf(separator.toLatin1());
        int t = msg.left(pos).toInt();

        readRequest(t, info, answer);
    }

    comm->send(QByteArray().append(answer.toStdString().c_str()));
}

void TApplication::readRequest(int t, requestInfo &info, QString& answer)
{
    switch (t)
    {
    case SET_PARAM_REQUEST:
        answer << QString().setNum(SET_PARAM_ANSWER);
        setNewParam(info.entrancesCount, info.floorsCount, info.maxLiftCapacity);
        break;
    case GO_LIFT_REQUEST:
        answer<<QString().setNum(GO_LIFT_ANSWER);
        break;
    case SEND_LOG_REQUEST:
        answer << QString().setNum(SEND_LOG_ANSWER);
        break;
    default: return;
    }
}

void TApplication::setNewParam(int entr, int flr, int cap)
{}


