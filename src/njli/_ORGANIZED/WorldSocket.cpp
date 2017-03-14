//
//  WorldSocket.cpp
//  JLIGameEngineTest
//
//  Created by James Folk on 1/16/15.
//  Copyright (c) 2015 James Folk. All rights reserved.
//

#include "WorldSocket.h"
#include "JLIFactoryTypes.h"

#include <unistd.h>
#include <errno.h>

//#ifdef __ANDROID__
#include <sys/socket.h>
//#endif

#include <netinet/tcp.h>
#include <arpa/inet.h>
#include <fcntl.h>

#include "Log.h"
#define TAG "WORLDSOCKET.CPP"
#define FORMATSTRING "{\"njli::WorldSocket\":[]}"
#include "btPrint.h"
#include "JsonJLI.h"

#include <string>

#define JLI_SOCKET_BUFFER_SIZE (65535)

namespace njli
{
    WorldSocket::WorldSocket():
    m_sck(-1),
    m_sck_addr(),
    m_buffer(new s8[JLI_SOCKET_BUFFER_SIZE]),
    m_isConnected(false),
    m_SocketData("")
    {
        m_sck_addr.sin_family = AF_INET;
        
        signal(SIGPIPE, SIG_IGN);
    }
    
    WorldSocket::~WorldSocket()
    {
        disconnectJLI();
        
        delete [] m_buffer;m_buffer=NULL;
    }
    
    const char *WorldSocket::getClassName()const
    {
        return "WorldSocket";
    }
    
    s32 WorldSocket::getType()const
    {
        return JLI_OBJECT_TYPE_WorldSocket;
    }
    
    WorldSocket::operator std::string() const
    {
        return njli::JsonJLI::parse(string_format("%s", FORMATSTRING));
    }
    
    bool WorldSocket::connectJLI(const char *ip, u16 port)
    {
        disconnectJLI();
        
        
        
        
        
        
        
        
        
        
        
        int res;
        struct sockaddr_in addr;
        long arg;
        fd_set myset;
        struct timeval tv;
        int valopt;
        socklen_t lon;
        
        // Create socket
        m_sck = socket(AF_INET, SOCK_STREAM, 0);
        if (m_sck < 0) {
            DEBUG_LOG_PRINT_E(TAG, "Error creating socket (%d %s)\n", errno, strerror(errno));
            disconnectJLI();return false;
        }
        
        addr.sin_family = AF_INET;
        addr.sin_port = htons(port);
        addr.sin_addr.s_addr = inet_addr(ip);
        
        // Set non-blocking
        if( (arg = fcntl(m_sck, F_GETFL, NULL)) < 0) {
            DEBUG_LOG_PRINT_E(TAG, "Error fcntl(..., F_GETFL) (%s)\n", strerror(errno));
            disconnectJLI();return false;
        }
        arg |= O_NONBLOCK;
        if( fcntl(m_sck, F_SETFL, arg) < 0) {
            DEBUG_LOG_PRINT_E(TAG, "Error fcntl(..., F_SETFL) (%s)\n", strerror(errno));
            disconnectJLI();return false;
        }
        // Trying to connect with timeout
        res = connect(m_sck, (struct sockaddr *)&addr, sizeof(addr));
        if (res < 0) {
            if (errno == EINPROGRESS) {
                DEBUG_LOG_PRINT_E(TAG, "%s", "EINPROGRESS in connect() - selecting\n");
                do {
                    tv.tv_sec = 1;
                    tv.tv_usec = 0;
                    FD_ZERO(&myset);
                    FD_SET(m_sck, &myset);
                    res = select(m_sck+1, NULL, &myset, NULL, &tv);
                    if (res < 0 && errno != EINTR) {
                        DEBUG_LOG_PRINT_E(TAG, "Error connecting %d - %s\n", errno, strerror(errno));
                        disconnectJLI();return false;
                    }
                    else if (res > 0) {
                        // Socket selected for write
                        lon = sizeof(int);
                        if (getsockopt(m_sck, SOL_SOCKET, SO_ERROR, (void*)(&valopt), &lon) < 0) {
                            DEBUG_LOG_PRINT_E(TAG, "Error in getsockopt() %d - %s\n", errno, strerror(errno));
                            disconnectJLI();return false;
                        }
                        // Check the value returned...
                        if (valopt) {
                            DEBUG_LOG_PRINT_E(TAG, "Error in delayed connection() %d - %s\n", valopt, strerror(valopt)
                                    );
                            disconnectJLI();return false;
                        }
                        m_isConnected = true;
                        return isConnected();
                    }
                    else {
                        DEBUG_LOG_PRINT_E(TAG, "%s", "Timeout in select() - Cancelling!\n");
                        disconnectJLI();return false;
                    }
                } while (1); 
            } 
            else { 
                DEBUG_LOG_PRINT_E(TAG, "Error connecting %d - %s\n", errno, strerror(errno)); 
                disconnectJLI();return false; 
            } 
        } 
        // Set to blocking mode again... 
        if( (arg = fcntl(m_sck, F_GETFL, NULL)) < 0) { 
            DEBUG_LOG_PRINT_E(TAG, "Error fcntl(..., F_GETFL) (%s)\n", strerror(errno)); 
            disconnectJLI();return false; 
        } 
        arg &= (~O_NONBLOCK); 
        if( fcntl(m_sck, F_SETFL, arg) < 0) { 
            DEBUG_LOG_PRINT_E(TAG, "Error fcntl(..., F_SETFL) (%s)\n", strerror(errno)); 
            disconnectJLI();return false; 
        } 
        // I hope that is all
        
        m_isConnected = true;
        return isConnected();
        
        
        
        
        
        
        
        
        
        
        
        
        
//        if(m_sck != -1)
//            return false;
//        
//        m_sck = socket( AF_INET, SOCK_STREAM, IPPROTO_TCP );
//        
//        if( m_sck < 0 )
//        { return 0; }
//        
//        m_sck_addr.sin_port = htons( port );
//        
//        if(1 == inet_pton( AF_INET, ip, &m_sck_addr.sin_addr ))
//        {
//            if(	connect( m_sck,
//                        ( struct sockaddr * )&m_sck_addr,
//                        sizeof( m_sck_addr )  ) < 0 )
//            {
//                disconnectJLI();
//                return false;
//            }
//            socketSetOpt();
//            
//            m_isConnected = true;
//        }
//        
//        return isConnected();
    }
    
//#include <algorithm>
//#include <functional>
//    // trim from start
//    static inline std::string &ltrim(std::string &s)
//    {
//        s.erase(s.begin(), std::find_if(s.begin(), s.end(), std::not1(std::ptr_fun<int, int>(std::isspace))));
//        return s;
//    }
//    
//    // trim from end
//    static inline std::string &rtrim(std::string &s)
//    {
//        s.erase(std::find_if(s.rbegin(), s.rend(), std::not1(std::ptr_fun<int, int>(std::isspace))).base(), s.end());
//        return s;
//    }
//    
//    // trim from both ends
//    static inline std::string &trim(std::string &s)
//    {
//        return ltrim(rtrim(s));
//    }
    
    static void ReplaceStringInPlace(std::string& subject, const std::string& search,
                                     const std::string& replace) {
        size_t pos = 0;
        while ((pos = subject.find(search, pos)) != std::string::npos) {
            subject.replace(pos, search.length(), replace);
            pos += replace.length();
        }
    }
    
    void WorldSocket::parseMessage(const std::string &delimeter)
    {
        if(isConnected())
        {
            s64 len = 0;
            
            if((len = recv(  m_sck,
                           &m_buffer[ 0 ],
                           JLI_SOCKET_BUFFER_SIZE,
                           0 )) > 0)
            {
                m_buffer[len] = '\0';
                std::string socketMessage(m_buffer);
                
                std::string fullStartDelimeter = "<" + delimeter + ">";
                std::string fullEndDelimeter = "</" + delimeter + ">";
                
                m_SocketData += socketMessage;
                
                unsigned long i = m_SocketData.find(fullStartDelimeter);
                unsigned long j = m_SocketData.find(fullEndDelimeter);
                if ( (i != -1) && (j != -1) )
                {
                    std::string extract = m_SocketData.substr(i, j + std::string(fullEndDelimeter).length());
                    std::string remainder = m_SocketData.substr(j + std::string(fullEndDelimeter).length(), m_SocketData.length());
                    m_SocketData = remainder;
                    
                    ReplaceStringInPlace(extract, "&lt;", "<");
                    ReplaceStringInPlace(extract, "&gt;", ">");
                    ReplaceStringInPlace(extract, "&amp;", "&");
                    ReplaceStringInPlace(extract, "&apos;", "'");
                    ReplaceStringInPlace(extract, "&quot;", "\"");
                    
                    m_MessageQueue.push(extract);
                }
                
            }
            
//            if(len!=-1)
//                DEBUG_LOG_V(TAG, "Received a message of %lld length", len);
            
        }
    }
    
    bool WorldSocket::hasMessage()const
    {
        return (m_MessageQueue.size() > 0);
    }
    
    std::string WorldSocket::popMessage()
    {
        std::string msg = m_MessageQueue.front();
        m_MessageQueue.pop();
        
//        DEBUG_LOG_V(TAG, "Parsed message..\n%s", msg.c_str());
        
        return msg;
    }
    
    void WorldSocket::sendMessage(const std::string &message)
    {
        
        
        
        if(isConnected())
        {
            size_t nbytes_sent = 0;
            nbytes_sent = send(m_sck,
                               message.c_str(),
                               message.length(),
                               0);
            
//            printf("Bytes_sent: %s -> %zu\n", message.c_str(), nbytes_sent);
        }
        
        
    }
    
    void WorldSocket::disconnectJLI()
    {
        if( m_sck > -1 )
        {
            close( m_sck );
            shutdown( m_sck, SHUT_RDWR );
            
            m_sck = -1;
        }
        
        m_isConnected = false;
    }
    
    bool WorldSocket::isConnected()const
    {
        return m_isConnected;
    }
    
    void WorldSocket::socketSetOpt()
    {
        int r = 0,
        v = 1;
        
        r = setsockopt( m_sck,
                       SOL_SOCKET,
                       SO_REUSEADDR,
                       (char *)&v, sizeof( v ) );
        
        
        r = setsockopt( m_sck,
                       IPPROTO_TCP,
                       TCP_NODELAY,
                       (char *)&v, sizeof( v ) );
        
        
        v = JLI_SOCKET_BUFFER_SIZE;
        
        r = setsockopt( m_sck,
                       SOL_SOCKET,
                       SO_SNDBUF,
                       (char *)&v, sizeof( v ) );
        
        
        r = setsockopt( m_sck,
                       SOL_SOCKET,
                       SO_RCVBUF,
                       (char *)&v, sizeof( v ) );	
        
        fcntl( m_sck, F_SETFL, O_NONBLOCK );
    }
}
