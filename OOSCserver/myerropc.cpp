#include "myerropc.h"
#include "def.h"


Myerr::Myerr()
{

}

void Myerr::MyErr_Driver_LoginInfo(QJsonObject& resp)
{
    resp.insert(HC_RESULT,QString(HC_ERR));
    resp.insert(HC_REASON,QString("Driver_LoginInfo happen error"));
}



void Myerr::MyErr_Passenger_LoginInfo(QJsonObject& resp)
{
    resp.insert(HC_RESULT,QString(HC_ERR));
    resp.insert(HC_REASON,QString("Passenger_LoginInfo happen error"));
}



void Myerr::MyErr_Driver_UpdateStatus(QJsonObject& resp)
{
    resp.insert(HC_RESULT,QString(HC_ERR));
    resp.insert(HC_REASON,QString("Driver_UpdateStatus happen error"));
}
