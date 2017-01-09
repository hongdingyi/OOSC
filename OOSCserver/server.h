#ifndef SERVER_H
#define SERVER_H

#include "def.h"
#include <QtSql/QSqlDatabase>
#include <tufao-1/Tufao/HttpServer>
#include <tufao-1/Tufao/HttpServerRequest>
#include <tufao-1/Tufao/HttpServerResponse>
using namespace Tufao;

class Server : public QObject
{
    Q_OBJECT

public:

    explicit Server(QObject *parent = 0);

    QByteArray  handle(QByteArray &request);

private:

    HttpServer*  server;

signals:

public slots:
    void slotRequestReady(Tufao::HttpServerRequest&,
                          Tufao::HttpServerResponse&);

};

#endif // SERVER_H





