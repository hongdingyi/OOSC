#include"server.h"
#include "util.h"
#include<QCoreApplication>

int main(int argc,char *argv[])
{
    QCoreApplication app(argc,argv);
    Util::instance()->Create_Dameno();
    new Server;
    return app.exec();
}
