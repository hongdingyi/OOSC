#ifndef REDISOPC_H
#define REDISOPC_H
#include<QJsonObject>

class Redis
{

public:

    static Redis* instance();

    QJsonObject Driver_LoginInfo(QString id,QString telphone,QString username,QString carid);

    QJsonObject Driver_WaitOrder(QString id,QString geohash,QString lat,QString lng);

    QJsonObject Driver_UpdateStatus(QString id,QString status);

    QJsonObject Driver_UpdateInfo(QString id,QString geohash,QString lat,QString lng);

    QJsonObject Passenger_WaitCar(QString id,QString geohash,QString lat,QString lng,QString dlat,QString dlng);

    QJsonObject Passenger_GetDriverInfo(QString id);

    QJsonObject Passenger_LoginInfo(QString id,QString telphone,QString username);

    QJsonObject Passenger_PayEnd(QString id,QString orderid,QString lat,QString lng,QString coast);

private:
    Redis();
};

#endif // REDISOPC_H
