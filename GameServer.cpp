#include "GameServer.h"
#include "event2/event.h"
#include "event2/util.h"
#include "event2/listener.h"

#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define MAXPROTOLEN 4096

#define CALLBACK_0(__selector__,__target__, ...) std::bind(&__selector__,__target__, ##__VA_ARGS__)
#define CALLBACK_1(__selector__,__target__, ...) std::bind(&__selector__,__target__, std::placeholders::_1, ##__VA_ARGS__)
#define CALLBACK_2(__selector__,__target__, ...) std::bind(&__selector__,__target__, std::placeholders::_1, std::placeholders::_2, ##__VA_ARGS__)
#define CALLBACK_3(__selector__,__target__, ...) std::bind(&__selector__,__target__, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3, ##__VA_ARGS__)

char buf[MAXPROTOLEN];

GameServer::GameServer(string ip, uint16 port)
{
    m_ip = ip;
    m_port = port;
}

GameServer::~GameServer()
{
    
}

void client_process_cb(evutil_socket_t fd, short what, void* arg)
{
    if(what & EV_READ)
    {
        int len = recv(fd, buf, MAXPROTOLEN, 0);
        if(len > 0)
        {
            cout<<"receive:"<<string(buf, len)<<endl;
            send(fd, buf, len, 0);
        }
    }
//    else if(what & EV_TIMEOUT)
//    {
//        event_free(processEvent);//todo
//        close(fd);
//    }
}

void listener_cb(evconnlistener* listener, evutil_socket_t fd, sockaddr* sa, int socklen, void* user_data)
{
    event_base* base = (event_base*)user_data;
    event* processEvent = event_new(base, fd, EV_READ|EV_PERSIST, client_process_cb, NULL);
    //timeval overTime = {60, 0};
    event_add(processEvent, NULL);
}

void GameServer::mainLoop()
{
    event_base* base = event_base_new();
    if(!base)
    {
        cout<<"create event_base failed!"<<endl;
        exit(0);
    }
    
    sockaddr_in sin;
    memset(&sin, 0, sizeof(sin));
    sin.sin_family = AF_INET;
    sin.sin_port = htons(m_port);
    if(inet_pton(AF_INET, m_ip.c_str(), &sin.sin_addr) <= 0)
    {
        cout<<"ip string format wrong!"<<endl;
        exit(0);
    }
    
    evconnlistener* listener = evconnlistener_new_bind(base, listener_cb, (void*)base, LEV_OPT_REUSEABLE|LEV_OPT_CLOSE_ON_FREE|LEV_OPT_CLOSE_ON_EXEC, -1, (sockaddr*)&sin, sizeof(sin));
    
    if(!listener)
    {
        cout<<"ip:"<<m_ip<<"port:"<<m_port<<endl;
        cout<<"create listener failed!"<<endl;
        exit(0);
    }
    
    event_base_dispatch(base);
    
    evconnlistener_free(listener);
    event_base_free(base);
    exit(0);
}
