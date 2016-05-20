//
//  IWSingleRoleThread.hpp
//  GameServer
//
//  Created by Apple on 4/13/16.
//  Copyright © 2016 Aloniki's Study. All rights reserved.
//

#ifndef IWSingleRoleThread_hpp
#define IWSingleRoleThread_hpp

#include "GameHeaders.h"
#include <string>
#include <vector>
#include <queue>
#include <pthread.h>
#include "Receiver.hpp"
#include "IBRoomClientHandler.hpp"
#include "Sender.hpp"

/// this class defines a thread to interact with roles
class IWSingleRoleThread {
protected:
    int connectfd;      //socket connection descriptor
    
    int iwRole;         //the role that is interacting with
    
    std::queue<DataPacket>* packetQueue;    //the queue of received data packets
    
    //thread IDs of receiver & handler
    pthread_t tidReceiver;
    pthread_t tidHandler;
    
    Receiver* receiver;
    Handler* handler;
    Sender* sender;
    
    
    
public:
    IWSingleRoleThread(int fd, int iwRole){     //structor
        this->connectfd = fd;
        this->iwRole = iwRole;
        
        packetQueue = new std::queue<DataPacket>();
        
        receiver = new Receiver(this->connectfd, this->packetQueue);
        handler = (Handler*)new IBRoomClientHandler(this->connectfd, this->packetQueue);
        sender = Sender::getSender();
    }
    ~IWSingleRoleThread(){      //destructor
        delete packetQueue;
        delete receiver;
        delete handler;
    }
    
    void run();     //run intercating thread
    void* runReceiver(void*);   //run a new receiver
    void* runHandler(void*);    //run a new handler
};

#endif /* IWSingleRoleThread_hpp */
