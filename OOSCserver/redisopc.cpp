#include "redisopc.h"
#include "def.h"
#include "myerropc.h"
#include "mysql.h"
#include <hiredis/hiredis.h>
#include<unistd.h>
#include <QDebug>
#include<QDateTime>
#include <iostream>
#include<QJsonObject>
#include<QJsonDocument>

Redis::Redis()
{

}


Redis* Redis::instance()
{
    static Redis* redis=new Redis;
    return redis;
}


QJsonObject Redis::Driver_LoginInfo(QString id,QString telphone,QString username,QString carid)
{    

    //when driver login success start write info to redis
    QDateTime time=QDateTime::currentDateTime();
    QString session=time.toString("yyyy-MM-dd-hh:mm:ss-dddd");//this is login time   
    redisContext *redis=redisConnect(HC_REDIS_HOST_IP,HC_REDIS_PORT);
    QJsonObject resp;
    char command[1000]={0};

    if(redis->err)
    {
        redisFree(redis);
        Myerr::MyErr_Driver_LoginInfo(resp);
        qDebug()<<"Driver_LoginInfo happen error 1";
        return resp;
    }

    sprintf(command,"hmset %s telphone %s username %s  carid %s status %s session %s geohash %s" ,
            QS2CH(id),QS2CH(telphone),QS2CH(username),QS2CH(carid),"busy",QS2CH(session),"0");

    redisReply *reply=(redisReply *)redisCommand(redis,command);
    if(NULL==reply)
    {
        redisFree(redis);
        Myerr::MyErr_Driver_LoginInfo(resp);
        qDebug()<<"Driver_LoginInfo happen error 2";
        return resp;
    }   
    freeReplyObject(reply);
    memset(command,0,sizeof(command));

    //this is very import because it can slove driver change point
    sprintf(command,"hset %s %s %s","0",QS2CH(telphone),QS2CH(telphone));
    reply=(redisReply *)redisCommand(redis,command);  
    qDebug()<<"Driver_LoginInfo success";
    freeReplyObject(reply);
    redisFree(redis);
    resp.insert(HC_RESULT,QString(HC_OK));
    return resp;
}




QJsonObject Redis::Driver_UpdateStatus(QString id,QString status)
{

    QJsonObject resp;
    redisContext *redis=redisConnect(HC_REDIS_HOST_IP,HC_REDIS_PORT);
    char command[1000]={0};
    if(redis->err)
    {
        redisFree(redis);
        Myerr::MyErr_Driver_UpdateStatus(resp);
        qDebug()<<"Driver_UpdateStatus happen error";
        return resp;
    }

    sprintf(command,"hset %s status %s",QS2CH(id),QS2CH(status));
    redisReply *reply=(redisReply *)redisCommand(redis,command);
    if(NULL==reply)
    {
        redisFree(redis);
        Myerr::MyErr_Passenger_LoginInfo(resp);
        qDebug()<<"Driver_UpdateStatus happen error";
        return resp;
    }
    qDebug()<<"Driver_UpdateStatus success";
    freeReplyObject(reply);
    redisFree(redis);
    resp.insert(HC_RESULT,QString(HC_OK));
    return resp;
}




QJsonObject Redis::Driver_WaitOrder(QString id,QString geohash,QString lat,QString lng)
{

    redisContext *redis=redisConnect(HC_REDIS_HOST_IP,HC_REDIS_PORT);
    QJsonObject resp;
    char command[1000]={0};
    sprintf(command,"hvals %s ",QS2CH(id));
    redisReply *reply=(redisReply *)redisCommand(redis,command);
    if(reply->type==REDIS_REPLY_ARRAY)
    {
        qDebug()<<"oldhash="<<reply->element[5]->str;
        //frist==>driver's newgeohash not equal oldgeohash
        if(geohash!=Element(5))
        {

            memset(command,0,sizeof(command));
            sprintf(command,"hdel %s %s",Element(5),QS2CH(id));//delete driver in oldgeohash
            reply=(redisReply *)redisCommand(redis,command);
            qDebug()<<"del  driver in oldgeohash happen success";
            freeReplyObject(reply);
            memset(command,0,sizeof(command));
            sprintf(command,"hset %s %s %s",QS2CH(geohash),QS2CH(id),QS2CH(id));
            reply=(redisReply *)redisCommand(redis,command);
            qDebug()<<"set driver in newgeohash happen success";

        }
        //second==> update driver info
        memset(command,0,sizeof(command));
        sprintf(command,"hmset %s geohash %s lat %s lng %s",QS2CH(id),QS2CH(geohash),QS2CH(lat),QS2CH(lng));
        qDebug()<<"command="<<command;
        reply=(redisReply *)redisCommand(redis,command);

        //thirdly=>check driver status
        freeReplyObject(reply);
        memset(command,0,sizeof(command));
        sprintf(command,"hvals %s ",QS2CH(id));
        reply=(redisReply *)redisCommand(redis,command);
        if(strcmp(Element(3),"busy")==0)//driver have order
        {
            qDebug()<<"driver have order";

            char orderid[100]={0};
            strcpy(orderid,reply->element[8]->str);

            //four==>get info form this orderid
            memset(command,0,sizeof(command));
            sprintf(command,"hvals %s",orderid);
            reply=(redisReply *)redisCommand(redis,command);
            if(reply->type==REDIS_REPLY_ARRAY)
            {
                resp.insert(HC_RESULT,QString("getorder"));
                resp.insert(HC_ORDERID,QString(orderid));
                resp.insert(HC_PPHONE,QString(Element(2)));
                resp.insert(HC_LAT,QString(Element(3)));
                resp.insert(HC_LNG,QString(Element(4)));
                resp.insert(HC_LAT,QString(Element(5)));
                resp.insert(HC_LNG,QString(Element(6)));
                redisFree(redis);
                return resp;
            }

        }
        else
        {
            qDebug()<<"have not order";
            resp.insert(HC_RESULT,QString(HC_OK));
            redisFree(redis);
            return resp;
        }

    }
    resp.insert(HC_RESULT,QString(HC_ERR));
    resp.insert(HC_REASON,QString("hvals driver happen error"));
    qDebug()<<"hvals driver happen error";
    freeReplyObject(reply);
    redisFree(redis);
    return resp;
}





QJsonObject Redis::Driver_UpdateInfo(QString id,QString geohash,QString lat,QString lng)
{

    redisContext *redis=redisConnect(HC_REDIS_HOST_IP,HC_REDIS_PORT);
    QJsonObject resp;
    char command[1000]={0};
    sprintf(command,"hvals %s ",QS2CH(id));
    redisReply *reply=(redisReply *)redisCommand(redis,command);
    if(reply->type==REDIS_REPLY_ARRAY)
    {
        qDebug()<<"oldhash="<<reply->element[5]->str;
        //frist==>driver's newgeohash not equal oldgeohash
        if(geohash!=Element(5))
        {

            memset(command,0,sizeof(command));
            sprintf(command,"hdel %s %s",Element(5),QS2CH(id));//delete driver in oldgeohash
            reply=(redisReply *)redisCommand(redis,command);
            qDebug()<<"del  driver in oldgeohash  success";
            freeReplyObject(reply);
            memset(command,0,sizeof(command));
            sprintf(command,"hset %s %s %s",QS2CH(geohash),QS2CH(id),QS2CH(id));
            reply=(redisReply *)redisCommand(redis,command);
            qDebug()<<"set driver in newgeohash  success";

        }
        //second==> update driver info
        memset(command,0,sizeof(command));
        sprintf(command,"hmset %s geohash %s lat %s lng %s",QS2CH(id),QS2CH(geohash),QS2CH(lat),QS2CH(lng));
        qDebug()<<"command="<<command;
        reply=(redisReply *)redisCommand(redis,command);
        redisFree(redis);
        resp.insert(HC_RESULT,QString(HC_OK));
        qDebug()<<"driverupdateinfo success";
        return resp;

    }
    resp.insert(HC_RESULT,QString(HC_ERR));
    resp.insert(HC_REASON,QString("driverupdateinfo happen error"));
    qDebug()<<"driverupdateinfo happen error";
    freeReplyObject(reply);
    redisFree(redis);
    return resp;
}






QJsonObject Redis::Passenger_LoginInfo(QString id,QString telphone,QString username)
{
    //when passenger login success start write info to redis
    QDateTime time=QDateTime::currentDateTime();
    QString session=time.toString("yyyy-MM-dd-hh:mm:ss-dddd");//this is login time
    redisContext *redis=redisConnect(HC_REDIS_HOST_IP,HC_REDIS_PORT);
    QJsonObject resp;
    char command[1000]={0};

    if(redis->err)
    {
        redisFree(redis);
        Myerr::MyErr_Passenger_LoginInfo(resp);
        qDebug()<<"Passenger_LoginInfo error";
        return resp;
    }

    sprintf(command,"hmset %s telphone %s username %s session %s",
            QS2CH(id),QS2CH(telphone),QS2CH(username),QS2CH(session));
    redisReply *reply=(redisReply *)redisCommand(redis,command);
    if(NULL==reply)
    {
        redisFree(redis);
        Myerr::MyErr_Passenger_LoginInfo(resp);
        qDebug()<<"Passenger_LoginInfo error";
        return resp;
    }

    qDebug()<<"Passenger_LoginInfo success";
    freeReplyObject(reply);
    redisFree(redis);
    resp.insert(HC_RESULT,QString(HC_OK));
    return resp;
}






QJsonObject Redis::Passenger_WaitCar(QString id,QString geohash,QString lat,QString lng,QString dlat,QString dlng)
 {

     int i = 0;
     int j = 0;
     static int move[21]={0,1,-1,2,-2,3,-3,4,-4,5,-5,6,-6,7,-7,8,-8,9,-9,10,-10};
     QJsonObject resp;
     char command[1000] = {0};
     redisReply *reply=NULL;
     redisContext *redis = redisConnect(HC_REDIS_HOST_IP,HC_REDIS_PORT);

     int point =geohash.toInt();
     qDebug()<<"point="<<point;
     while(i!=20)
     {
         memset(command,0,sizeof(command));
         sprintf(command,"hvals %d",point+move[i]);
         qDebug()<<"hvals point+move[i]=%s"<<command;
         char OldCommand[1000]={0};
         strcpy(OldCommand,command);
         reply=(redisReply *)redisCommand(redis,command);         
         int num=reply->elements;
         qDebug()<<"this point num="<<num;
         for(j=0;j<num;j++)
         {             
             memset(command,0,sizeof(command));
             qDebug()<<"driver telphone="<<reply->element[j]->str;
             sprintf(command,"hvals %s",reply->element[j]->str);
             qDebug()<<"reply->element[j]->str="<<command;
             reply=(redisReply *)redisCommand(redis,command);
             qDebug()<<"this driver's status="<<Element(3);
             if(strcmp(Element(3),"free")==0)//this driver is free now
              {
                     char orderid[1000]={0};
                     qDebug()<<"waitcar success";                     

                     //frist==>create orderid by passenger phone
                     sprintf(orderid,"orderid%s",QS2CH(id));
                     qDebug()<<"orderid="<<orderid;

                     //second==>resp to passenger
                     resp.insert(HC_RESULT,QString(HC_OK));
                     resp.insert(HC_ORDERID,QString(orderid));
                     resp.insert(HC_TELPHONE,QString(Element(0)));
                     resp.insert(HC_CARID,QString(Element(2)));
                     resp.insert(HC_LAT,QString(Element(6)));
                     resp.insert(HC_LNG,QString(Element(7)));

                     QString dphone=Element(0);
                     QString carid=Element(2);

                     //thirdly==>change this driver info
                     memset(command,0,sizeof(command));
                     sprintf(command,"hmset %s status %s orderid %s",
                          Element(0),"busy",orderid);
                     reply=(redisReply *)redisCommand(redis,command);
                     qDebug()<<"change this driver info success";

                     //four==>create order
                     freeReplyObject(reply);
                     memset(command,0,sizeof(command));                     
                     sprintf(command,"hmset %s dphone %s carid %s pphone %s slat %s slng %s dlat %s dlng %s",
                          orderid,QS2CH(dphone),QS2CH(carid),QS2CH(id),QS2CH(lat),QS2CH(lng),QS2CH(dlat),QS2CH(dlng));
                     reply=(redisReply *)redisCommand(redis,command);
                     freeReplyObject(reply);
                     redisFree(redis);
                     return resp;             
              }
             reply=(redisReply *)redisCommand(redis,OldCommand);//this is very important
           }
         i++;//go  to next geohash
         sleep(1);
     }
     resp.insert(HC_RESULT,QString(HC_ERR));
     resp.insert(HC_REASON,QString("this time have not car"));
     qDebug()<<"this time have not car";     
     redisFree(redis);
     return resp;

 }






QJsonObject Redis::Passenger_PayEnd(QString id,QString orderid,QString lat,QString lng,QString coast)
{

    Mysql * mysql=Mysql::initance();
    QDateTime time=QDateTime::currentDateTime();
    QString ordertime=time.toString("yyyy-MM-dd-hh:mm:ss-dddd");
    QJsonObject resp;
    char command[1000] = {0};
    redisReply *reply=NULL;
    redisContext *redis = redisConnect(HC_REDIS_HOST_IP,HC_REDIS_PORT);

    //frist==>delete passenger by id
    sprintf(command,"del %s",QS2CH(id));
    qDebug()<<"del passenger="<<command;
    reply=(redisReply *)redisCommand(redis,command);
    qDebug()<<"del passenger success";

    //second==>update oderid
    freeReplyObject(reply);
    memset(command,0,sizeof(command));
    sprintf(command,"hmset %s dlat %s dlng %s coast %s ordertime %s",
    QS2CH(orderid),QS2CH(lat),QS2CH(lng),QS2CH(coast),QS2CH(ordertime));
    reply=(redisReply *)redisCommand(redis,command);
    qDebug()<<"update oderid success";


    memset(command,0,sizeof(command));
    sprintf(command,"hvals %s",QS2CH(orderid));   
    reply=(redisReply *)redisCommand(redis,command);

    if(reply->type==REDIS_REPLY_ARRAY)
    {


        QString sql=QString("insert into ordertable values('%1','%2','%3','%4','%5',").
        arg(orderid,Element(0),Element(1),Element(2),Element(3));
        sql=sql+QString("'%1','%2','%3','%4','%5')").
                arg(Element(4),Element(5),Element(6),Element(7),Element(8));
        qDebug()<<"sql="<<sql;
        qDebug()<<"sleep(10)";
        sleep(10);

        //thirdly==>del order by orderid
        memset(command,0,sizeof(command));
        sprintf(command,"del %s",QS2CH(orderid));
        reply=(redisReply *)redisCommand(redis,command);
        qDebug()<<"del order success";

        //last==>insert into mysql
        resp=mysql->insert(sql);
        redisFree(redis);
        return resp;
    }

    redisFree(redis);
    resp.insert(HC_RESULT,QString(HC_ERR));
    resp.insert(HC_REASON,QString("passenger payend happen error"));
    qDebug()<<"passenger payend happen error";
    return resp;
}






QJsonObject Redis::Passenger_GetDriverInfo(QString id)
{

     redisContext *redis=redisConnect(HC_REDIS_HOST_IP,HC_REDIS_PORT);
     QJsonObject resp;
     char command[1000]={0};
     sprintf(command,"hvals %s ",QS2CH(id));
     redisReply *reply=(redisReply *)redisCommand(redis,command);
     if(reply->type==REDIS_REPLY_ARRAY)
     {
         resp.insert(HC_RESULT,QString(HC_OK));
         resp.insert(HC_LAT,QString(Element(6)));
         resp.insert(HC_LNG,QString(Element(7)));
         qDebug()<<"passenger getdriverinfo success";
         redisFree(redis);
         return resp;
     }
     resp.insert(HC_RESULT,QString(HC_ERR));
     resp.insert(HC_REASON,QString("passenger getdriverinfo happen error"));
     qDebug()<<"passenger getdriverinfo happen error";
     freeReplyObject(reply);
     redisFree(redis);
     return resp;

 }

























