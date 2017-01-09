#include "mysql.h"
#include "def.h"
#include "redisopc.h"
#include<QtSql/QSqlDatabase>
#include<QtSql/QSqlQuery>
#include<QtSql/QSqlError>
#include<QJsonObject>
#include<QDebug>

Mysql::Mysql()
{
}



Mysql * Mysql::initance()
{
   static Mysql * mysql=new Mysql;
   return mysql;
}



void Mysql::create()
{
    db=QSqlDatabase::addDatabase(HC_dbType);
    db.setHostName(HC_dbHost_IP);
    db.setPort(HC_dbPort);
    db.setUserName(HC_dbUserName);
    db.setPassword(HC_dbPassWord);
    db.setDatabaseName(HC_dbName);
    if(!db.open())
    {
        qDebug()<<"open db error";
        exit(0);
    }
    qDebug()<<"open db ok";
}



QJsonObject Mysql::insert(QString sql)
{
    QJsonObject resp;
    QSqlQuery query=db.exec(sql);
    QSqlError error=db.lastError();

    //reg success
    if(error.type()==QSqlError::NoError)
    {

        resp.insert(HC_RESULT,QString(HC_OK));
        qDebug()<<"insert into mysql Success";
        return resp;
    }

    //reg error
    resp.insert(HC_RESULT,QString(HC_ERR));
    resp.insert(HC_REASON,QString("insert into mysql Error"));
    qDebug()<<"insert into mysql Error";
    return resp;
}


QJsonObject Mysql::auth(QString sql,QString password,QString role)
{
    QJsonObject resp;
    QSqlQuery query=db.exec(sql);
    QSqlError error=db.lastError();

    if(error.type()==QSqlError::NoError)
    {
        //have no result  for research
        if(!query.next())
       {
        resp.insert(HC_RESULT,QString(HC_ERR));
        resp.insert(HC_REASON,QString("this user is not exist"));
        qDebug()<<"this user is not exist";
        return resp;
       }
        //the password is error
        if(password!=query.value(2).toString())
        {
         resp.insert(HC_RESULT,QString(HC_ERR));
         resp.insert(HC_REASON,QString("password is error"));
         qDebug()<<"password is error";
         return resp;
        }

        if(role=="passenger")
        {
            resp=Redis::instance()->Passenger_LoginInfo(Value(0),Value(0),Value(1));
            return resp;
        }

        else
        {
            QString Newrole=query.value(3).toString();
            //when driver login success start write info to redis
            if(Newrole==role)
            {
                resp=Redis::instance()->Driver_LoginInfo(Value(0),Value(0),Value(1),Value(4));
                return resp;
            }
            else
            {

                resp.insert(HC_RESULT,QString(HC_ERR));
                resp.insert(HC_REASON,QString("you are not driver now"));
                qDebug()<<"you are not driver now";
                return resp;
            }

        }

    }

    else
    {
        resp.insert(HC_RESULT,QString(HC_ERR));
        resp.insert(HC_REASON,error.text());
        return resp;
    }
}











