#ifndef COMMON_H
#define COMMON_H

#include <QString>

enum messages
{
    SET_PARAM_REQUEST,
    SET_PARAM_ANSWER,
    GO_LIFT_REQUEST,
    GO_LIFT_ANSWER,
    SEND_LOG_REQUEST,
    SEND_LOG_ANSWER,
};

enum modes
{
    D_MODE = 1,
    C_MODE,
    R_MODE,
};

extern const QChar separator;
QString& operator<< (QString&,const QString&);

#endif // COMMON_H
