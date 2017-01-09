#include "server.h"
#include "serveropc.h"
#include "def.h"
#include"redisopc.h"
#include"mysql.h"
#include<hiredis/hiredis.h>
#include<QJsonObject>
#include<QJsonValue>
#include<QJsonDocument>
#include<QJsonArray>


Server::Server(QObject *parent) :
    QObject(parent)
{
    Mysql *mysql=Mysql::initance();
    mysql->create();
    server=new HttpServer;
    connect(server,&HttpServer::requestReady,
            this,&Server::slotRequestReady);

    if(server->listen(QHostAddress::Any,HC_SERVER_PORT))
    {
        qDebug()<<"listen ok";
    }
    else
    {
        qDebug()<<"listen error";
    }

}


QByteArray Server::handle(QByteArray &request)
{
    QJsonDocument doc=QJsonDocument::fromJson(request);
    QJsonObject obj=doc.object();
    QString cmd=obj.value(HC_CMD).toString();
    QJsonObject resp;     
    qDebug()<<"cmd="<<cmd;
    if(cmd==HC_REG)
    {
        resp=Serveropc::instance()->Reg(obj);
    }
    else if(cmd==HC_LOGIN)
    {
        resp=Serveropc::instance()->Login(obj);
    }
    else if(cmd==HC_UPDATESTATUS)
    {
        resp=Serveropc::instance()->UpdateStatus(obj);
    }
    else if(cmd==HC_WAITORDER)
    {
        resp=Serveropc::instance()->WaitOrder(obj);
    }
    else if(cmd==HC_WAITCAR)
    {
        resp=Serveropc::instance()->WaitCar(obj);
    }
    else if(cmd==HC_UPDATEINFO)
    {
        resp=Serveropc::instance()->UpdateInfo(obj);
    }
    else if(cmd==HC_GETDRIVERINFO)
    {
        resp=Serveropc::instance()->GetDriverInfo(obj);
    }
    else if(cmd==HC_PAYEND)
    {
        resp=Serveropc::instance()->PayEnd(obj);
    }

    else
    {
        resp.insert(HC_RESULT,QString(HC_ERR));
        resp.insert(HC_REASON,QString("you cmd is error"));
    }
    return QJsonDocument(resp).toJson();
}



void Server::slotRequestReady(HttpServerRequest & request,HttpServerResponse &response)
{

    connect(&request,&HttpServerRequest::end,[&]()
    {

        QByteArray buf=request.readBody();
        QByteArray resp=handle(buf);
        response.writeHead(HttpResponseStatus::OK);
        response.end(resp);

    }
    );
}











