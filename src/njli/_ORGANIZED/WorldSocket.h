//
//  WorldSocket.h
//  JLIGameEngineTest
//
//  Created by James Folk on 1/16/15.
//  Copyright (c) 2015 James Folk. All rights reserved.
//

#ifndef __JLIGameEngineTest__WorldSocket__
#define __JLIGameEngineTest__WorldSocket__

#include <netinet/in.h>
//#include <netinet/tcp.h>
//#include <arpa/inet.h>
//#include <fcntl.h>
#include "AbstractObject.h"
#include <queue>
#include <string>

#include "File.h"

namespace njli {
/// <#Description#>
class WorldSocket : public AbstractObject {
public:
    using AbstractDecorator::setName;
    using AbstractDecorator::getName;

    /**
         *  <#Description#>
         */
    WorldSocket();
    /**
         *  <#Description#>
         *
         *  @return <#return value description#>
         */
    virtual ~WorldSocket();

    /**
         *  <#Description#>
         *
         *  @return <#return value description#>
         */
    virtual const char* getClassName() const;
    /**
         *  <#Description#>
         *
         *  @return <#return value description#>
         */
    virtual s32 getType() const;
    /**
         *  <#Description#>
         *
         *  @return <#return value description#>
         */
    virtual operator std::string() const;

public:
    //TODO: fill in specific methods for WorldSocket

    /**
         *  <#Description#>
         *
         *  @param ip   <#ip description#>
         *  @param port <#port description#>
         *
         *  @return <#return value description#>
         */
    bool connectJLI(const char* ip, u16 port);

    void parseMessage(const std::string& delimeter = "root");
    bool hasMessage() const;
    std::string popMessage();

    void sendMessage(const std::string& message);
    /**
         *  <#Description#>
         */
    void disconnectJLI();
    /**
         *  <#Description#>
         *
         *  @return <#return value description#>
         */
    bool isConnected() const;

protected:
    void socketSetOpt();

private:
    WorldSocket(const WorldSocket&);
    WorldSocket& operator=(const WorldSocket&);

    s32 m_sck;
    struct sockaddr_in m_sck_addr;
    s8* m_buffer;
    bool m_isConnected;

    std::string m_SocketData;

    std::queue<std::string> m_MessageQueue;
};
}

#endif /* defined(__JLIGameEngineTest__WorldSocket__) */
