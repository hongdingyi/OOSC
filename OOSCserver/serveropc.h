#ifndef SERVEROPC_H
#define SERVEROPC_H

#include<QJsonObject>
#include<QJsonValue>
#include<QJsonDocument>
#include<QJsonArray>
#include<QCryptographicHash>

class Serveropc
{

public:
    static Serveropc *instance();

    QJsonObject Reg(QJsonObject& req);

    QJsonObject Login(QJsonObject& req);

    QJsonObject WaitOrder(QJsonObject& req);

    QJsonObject WaitCar(QJsonObject& req);

    QJsonObject UpdateInfo(QJsonObject& req);

    QJsonObject UpdateStatus(QJsonObject& req);

    QJsonObject GetDriverInfo(QJsonObject& req);

    QJsonObject PayEnd(QJsonObject& req);

private:
    Serveropc();

};

#endif // SERVEROPC_H
