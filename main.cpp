#include <unistd.h>
#include <sys/wait.h>
//#include <signal.h>
#include "Config.h"
#include "GameServer.h"
//#include <stdio.h>

int main(int argc, char** args)
{
    Config* pMainConfig = new Config();
    if(pMainConfig)
        pMainConfig->configIn("config.ini");
    else
    {
        cout<<"config init wrong!"<<endl;
        return 0;
    }
    uint16_t port = pMainConfig->getInt("port", 5001);
    string ip = pMainConfig->getStr("ip", "127.0.0.1");
    cout<<"listen at: "<<ip<<":"<<port<<endl;
    
    while(1)
    {
        pid_t pid = fork();
        if(pid < 0)
        {
            cout<<"fork child pid wrong!"<<endl;
        }
        else if(pid > 0)
        {
            int status;
            pid = wait(&status);
            cout<<"child has been exit!pid="<<pid<<endl;
        }
        else
        {
            
            GameServer* pServer = new GameServer(ip, port);
            if(pServer)
                pServer->mainLoop();
            else
            {
                cout<<"create GameSever wrong!"<<endl;
                exit(0);
            }
        }
    }
    return 0;
}
