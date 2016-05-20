//
//  Sender.hpp
//  GameRoom
//
//  Created by Apple on 5/6/16.
//  Copyright © 2016 Aloniki's Study. All rights reserved.
//

#ifndef Sender_hpp
#define Sender_hpp

#include <unistd.h>
#include <arpa/inet.h>
#include <pthread.h>
#include <iostream>
#include "GameHeaders.h"
#include "RoomManager.hpp"
#include "PortManager.hpp"

/**
 * this sender is connected to server, it is a single instance.
 */
class Sender {
protected:
    static Sender* sender;      //single instance
    Sender();                   //constructor
    ~Sender(){
        delete sender;
    };                //destructor
    
    bool init();                //initialize connection
    
    bool isConnected;           //connection state flag
    
    int                     sockfd;
    struct sockaddr_in      servaddr;
public:
    static Sender* getSender();        //get static instance
    bool send(R2SSignal, void*);   //send signal & data to the server
};

#endif /* Sender_hpp */
