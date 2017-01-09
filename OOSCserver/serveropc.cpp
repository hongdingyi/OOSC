#include "serveropc.h"
#include "def.h"
#include "redisopc.h"
#include "mysql.h"
#include<QVariant>
#include<QDebug>

Serveropc::Serveropc()
{

}

 Serveropc *Serveropc::instance()
 {
     static Serveropc* serveropc=new Serveropc;
     return serveropc;
 }

//this is register
 QJsonObject Serveropc::Reg(QJsonObject &req)
 {
     Mysql *mysql=Mysql::initance();
     QJsonObject resp;

     QString telphone=req.value(HC_TELPHONE).toString();
     QString username=req.value(HC_USERNAME).toString();
     QString password=req.value(HC_PASSWORD).toString();
     QString role=req.value(HC_ROLE).toString();
     QString carid=req.value(HC_CARID).toString();
     QString sql=QString("insert into usertable values('%1','%2','%3','%4','%5')")
             .arg(telphone,username,password,role,carid);
     qDebug() << "Reg_Command="<<sql;
     resp=mysql->insert(sql);
     return resp;
 }




 //this is login
 QJsonObject Serveropc::Login(QJsonObject &req)
 {
     Mysql *mysql=Mysql::initance();
     QJsonObject resp;
     QString telphone=req.value(HC_TELPHONE).toString();
     QString password=req.value(HC_PASSWORD).toString();
     QString role=req.value(HC_ROLE).toString();
     qDebug()<<"Login:telphone="<<QS2CH(telphone)<<"password="<<QS2CH(password)<<"role="<<QS2CH(role);
     QString sql=QString("select * from usertable where telphone = '%1'").arg(telphone);
     resp=mysql->auth(sql,password,role);
     return resp;
 }


 //driver updatestatus
 QJsonObject Serveropc::UpdateStatus(QJsonObject &req)
 {

     QJsonObject resp;
     QString telphone=req.value(HC_TELPHONE).toString();
     QString status=req.value(HC_STATUS).toString();
     qDebug()<<"UpdateStatus:telphone="<<telphone<<"status="<<status;     
     resp=Redis::instance()->Driver_UpdateStatus(telphone,status);
     return resp;

 }


//driver waitorder
QJsonObject Serveropc::WaitOrder(QJsonObject& req)
{
    QJsonObject resp;
    QString telphone=req.value(HC_TELPHONE).toString();
    QString geohash=req.value(HC_GEOHASH).toString();
    QString lat=req.value(HC_LAT).toString();
    QString lng=req.value(HC_LNG).toString();
    qDebug()<<"driverWaitOrder: telphone="<<telphone<<"geohash="<<geohash<<"lat="<<lat<<"lng="<<lng;   
    resp=Redis::instance()->Driver_WaitOrder(telphone,geohash,lat,lng);
    return resp;
}


//driver updateinfo
QJsonObject Serveropc::UpdateInfo(QJsonObject& req)
{
    QJsonObject resp;
    QString telphone=req.value(HC_TELPHONE).toString();
    QString geohash=req.value(HC_GEOHASH).toString();
    QString lat=req.value(HC_LAT).toString();
    QString lng=req.value(HC_LNG).toString();
    qDebug()<<"driverupdateinfo:telphone="<<telphone<<"geohash="<<geohash<<"lat="<<lat<<"lng="<<lng;
    resp=Redis::instance()->Driver_UpdateInfo(telphone,geohash,lat,lng);
    return resp;
}


//passenger waitcar
QJsonObject Serveropc::WaitCar(QJsonObject& req)
{
    QJsonObject resp;
    QString telphone=req.value(HC_TELPHONE).toString();
    QString geohash=req.value(HC_GEOHASH).toString();
    QString lat=req.value(HC_LAT).toString();
    QString lng=req.value(HC_LNG).toString();
    QString dlat=req.value(HC_DLAT).toString();
    QString dlng=req.value(HC_DLNG).toString();
    qDebug()<<"passengerWaitCar:telphone="<<telphone<<"geohash="<<geohash<<"lat="<<lat<<"lng="<<lng<<"dlat="<<dlat<<"dlng="<<dlng;
    resp=Redis::instance()->Passenger_WaitCar(telphone,geohash,lat,lng,dlat,dlng);
    return resp;
}


//passenger getdriverinfo
QJsonObject Serveropc::GetDriverInfo(QJsonObject& req)
{
    QJsonObject resp;
    QString telphone=req.value(HC_TELPHONE).toString();
    qDebug()<<"passenger getdriverinfo:telphone="<<telphone;
    resp=Redis::instance()->Passenger_GetDriverInfo(telphone);
    return resp;
}



//passenger PayEnd
QJsonObject Serveropc::PayEnd(QJsonObject& req)
{
    QJsonObject resp;
    QString telphone=req.value(HC_TELPHONE).toString();
    QString orderid=req.value(HC_ORDERID).toString();
    QString lat=req.value(HC_LAT).toString();
    QString lng=req.value(HC_LNG).toString();
    QString coast=req.value(HC_COAST).toString();
    qDebug()<<"passenger payend:telphone="<<telphone<<"orderid="<<orderid<<"lat="<<lat<<"lng="<<lng<<"coast="<<coast;
    resp=Redis::instance()->Passenger_PayEnd(telphone,orderid,lat,lng,coast);
    return resp;
}









