//
//  Receiver.hpp
//  GameServer
//
//  Created by Apple on 4/13/16.
//  Copyright © 2016 Aloniki's Study. All rights reserved.
//

#ifndef Receiver_hpp
#define Receiver_hpp

#include "GameHeaders.h"
#include <vector>
#include <queue>
#include <pthread.h>
#include <unistd.h>
//#include <iostream>

/*
//this class defines a common receiver; it is used to receiver TCP flows and convert them into
//formal data packets
*/
class Receiver {
protected:
    int connectfd;                      //socket connection identifier
    
    size_t recvCount;                   //the count of received data
    size_t packetLength;                //the length of a packet
    char recv[MAXLINE];                 //saves the data in one read
    char buf[MAXLINE];                  //saves the hole unpakcet data
    char head[DATALENGTH + 1];          //saves the packet length
    
    std::queue<DataPacket>* packetQueue; //saves the formal packet
public:
    Receiver(int fd, std::queue<DataPacket>* packetQueue){      //structor
        this->connectfd = fd;
        this->packetQueue = packetQueue;
        this->recvCount = 0;
        this->packetLength = 0;
    }
    void receive();     //receive TCP flows
    void addToPacketQueue(std::string*); //add & convert received data into the queue of packets
};

#endif /* Receiver_hpp */
