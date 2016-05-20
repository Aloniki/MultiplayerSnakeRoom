//
//  Sender.cpp
//  GameRoom
//
//  Created by Apple on 5/6/16.
//  Copyright © 2016 Aloniki's Study. All rights reserved.
//

#include "Sender.hpp"
#include <random>

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
        if (false == sender->init()) {
            std::cout<<"init fails, try again!"<<std::endl;
        }
    }
    return sender;
}

bool Sender::send(R2SSignal signal, void* data){
    std::string packet;
    switch (signal) {
        case R2SSignal::CLOSED:{
            std::stringstream ss;
            ss<<*((int*)data);
            auto sid = ss.str();
            
            packet = DataPacketProtocol::Pack(ROOMROLE, R2SSignal::CLOSED, &sid);
            std::cout<<"I'm dying now!"<<std::endl;
            break;
        }
        case R2SSignal::CREATED:{
            std::string jri = "";
            auto roomInfo = (RoomInfo*)data;
            JsonManager::RoomInfoToJson(roomInfo, jri);
            packet = DataPacketProtocol::Pack(ROOMROLE, R2SSignal::CREATED, &jri);
            std::cout<<"I'm created now!"<<std::endl;
            std::cout<<jri<<std::endl;
            
            
            break;
        }
        case R2SSignal::STARTED:{
            std::stringstream ss;
            ss<<*((int*)data);
            auto sid = ss.str();
            
            packet = DataPacketProtocol::Pack(ROOMROLE, R2SSignal::STARTED, &sid);
            std::cout<<"I'm going to start now!"<<std::endl;
            break;
        }
        case R2SSignal::UPDATED:{
            std::string jri = "";
            auto roomInfo = (RoomInfo*)data;
            JsonManager::RoomInfoToJson(roomInfo, jri);
            packet = DataPacketProtocol::Pack(ROOMROLE, R2SSignal::UPDATED, &jri);
            std::cout<<"I'm going to inform the server to update room info!"<<std::endl;
            break;
        }
            
        default:
            break;
    }
    
    if (true == FullWrite(this->sockfd, packet)) {
        std::cout<<"Full write successed"<<std::endl;
        return true;
    }
    std::cout<<"Full write failed!"<<std::endl;
    return false;
}


void Sender::closeSender(){
    close(this->sockfd);
}


















