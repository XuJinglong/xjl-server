#ifndef _GameServer_h
#define _GameServer_h

#include "common.h"
/******************************
#ifdef __cplusplus
extern "C"{
#endif
#include "event2/event.h"
#ifdef __cplusplus
}
#endif
 不需要这样,libevent自己做了兼融c++的处理
 *******************************/

class GameServer
{
public:
    GameServer(string ip, uint16 port);
    virtual ~GameServer();
    void mainLoop();
private:
    string m_ip;
    uint16 m_port;
};

#endif
