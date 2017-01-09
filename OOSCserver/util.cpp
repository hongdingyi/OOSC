#include "util.h"
#include<unistd.h>
#include<signal.h>
#include<stdlib.h>
void Util::Create_Dameno()
{
    signal(SIGCHLD,SIG_IGN);
    signal(SIGHUP,SIG_IGN);
    signal(SIGINT,SIG_IGN);
    pid_t pid=fork();
    if(pid==0)
    {
        exit(0);
    }
    setsid();
    pid=fork();
    if(pid==0)
    {
        exit(0);
    }

}

Util* Util::instance()
{
    static Util * util=new Util;
    return util;
}

Util::Util()
{

}
