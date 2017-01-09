#ifndef MYSQL_H
#define MYSQL_H
#include <QtSql/QSqlDatabase>
#include<QJsonObject>

class Mysql
{

public:

     static Mysql * initance();

     void create();

     QJsonObject insert(QString sql);

     QJsonObject auth(QString sql,QString password,QString role);

private:

     Mysql();
     QSqlDatabase db;
};

#endif // MYSQL_H
