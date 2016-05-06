//
//  ServerDaemon.hpp
//  GameServer
//
//  Created by Apple on 4/12/16.
//  Copyright © 2016 Aloniki's Study. All rights reserved.
//

#ifndef ServerDaemon_hpp
#define ServerDaemon_hpp

#include "GameHeaders.h"
#include <iostream>
#include <arpa/inet.h>
#include <pthread.h>
#include <vector>
#include "IWSingleRoleThread.hpp"

/// ServerDaemon class
class ServerDaemon {
protected:
    int                 iwRole;     //the role that is interacting with
    in_port_t           port;       //using port
    
    int                 listenfd;   //listen socket descriptor
    int                 connfd;     //connect socket dscriptor
    socklen_t           clilen;     //address length
    struct sockaddr_in  cliaddr;    //socket address
    struct sockaddr_in  servaddr;   //server socket address
    
    std::vector<pthread_t>* tidList;    //threads IDs list
    
    ~ServerDaemon(){    //destructor
        delete tidList;
    }
    
public:
    ServerDaemon(int iwRole){   //structor
        this->tidList = new std::vector<pthread_t>();
        this->iwRole = iwRole;
        this->port = IBCRPort;
    }
    bool initDaemon();      //initialize daemon
    void run();     //run daemon
    void* newIWSingleRoleThread(void*);     //run a new thread to interact with role
};

#endif /* ServerDaemon_hpp */
