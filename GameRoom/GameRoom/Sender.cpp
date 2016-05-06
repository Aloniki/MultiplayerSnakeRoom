//
//  Sender.cpp
//  GameRoom
//
//  Created by Apple on 5/6/16.
//  Copyright © 2016 Aloniki's Study. All rights reserved.
//

#include "Sender.hpp"

Sender* Sender::sender;

Sender::Sender(){
    //set up a tcp connection
    this->sockfd = socket(AF_INET, SOCK_STREAM, 0);
    //empty the servaddr
    bzero(&(this->servaddr), sizeof(this->servaddr));
    
    /**
     *  set the value servaddr
     */
    this->servaddr.sin_family = AF_INET;
    this->servaddr.sin_port   = htons(IBSRPort);
    inet_pton(AF_INET, ServIPAddr, &(this->servaddr.sin_addr));
}

bool Sender::init(){
    //connect to the server
    int connectResult = connect(this->sockfd, (struct sockaddr*)&(this->servaddr),
                                sizeof(this->servaddr));
    std::cout<<"connect result"<<connectResult<<std::endl;
    
    if (0 == connectResult) {
        this->isConnected = true;
        return true;
    }else {
        if (-1 == connectResult) {
            this->isConnected = false;
            close(this->sockfd);
            std::cout<<"error: "<<errno<<std::endl;
        }
        return false;
    }
}


Sender* Sender::getSender(){
    if (NULL == sender) {
        sender = new Sender();
        init:
        if (false == sender->init()) {
            std::cout<<"init fails, try again!"<<std::endl;
            goto init;
        }
    }
    return sender;
}

bool Sender::send(R2SSignal singal){
    auto packet = DataPacketProtocol::Pack(ROOMROLE, singal);
    auto c_packet = packet.c_str();
    auto length = strlen(c_packet);
    auto wCount = 0;
    auto rCount = length;
    ssize_t n = 0;
    while (true) {
        n = write(this->sockfd, c_packet, rCount);
        if (-1 == n) {
            std::cout<<"error:"<<errno<<std::endl;
            return false;
        }
        wCount += n;
        if (wCount >= length) {
            break;
        }
        c_packet += wCount;
        rCount -= wCount++;
    }
    return true;
}




















