#ifndef MYERROPC_H
#define MYERROPC_H
#include<QJsonObject>

class Myerr
{

public:

    static void MyErr_Driver_LoginInfo(QJsonObject& resp);

    static void MyErr_Driver_UpdateStatus(QJsonObject& resp);

    static void MyErr_Passenger_LoginInfo(QJsonObject& resp);

private:
    Myerr();
};

#endif // MYERROPC_H
