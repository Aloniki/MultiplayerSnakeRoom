//
//  Sender.cpp
//  GameRoom
//
//  Created by Apple on 5/6/16.
//  Copyright © 2016 Aloniki's Study. All rights reserved.
//

#include "Sender.hpp"
#include <random>


int Sender::connectToRole(int role, int port){
    //set up a tcp connection
    int socketfd = socket(AF_INET, SOCK_STREAM, 0);
    struct sockaddr_in servaddr;
    memset(&servaddr, 0, sizeof(servaddr));
    servaddr.sin_len = sizeof(servaddr);
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(port);
    inet_pton(AF_INET, ServIPAddr, &servaddr.sin_addr);
    //connect to the server
    int connectResult = connect(socketfd, (struct sockaddr*)&servaddr,
                                sizeof(servaddr));
    std::cout<<"connect result"<<connectResult<<std::endl;
    
    if (0 == connectResult) {
        return socketfd;
    }else {
        close(socketfd);
        std::cout<<"error: "<<errno<<std::endl;
        return socketfd;
    }
}

bool Sender::send(int role, int socketfd, int signal, void *data){
    std::string packet;
    switch (role) {
        case SERVERROLE:
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
            break;
            
        default:
            break;
    }
        if (true == FullWrite(socketfd, packet)) {
        std::cout<<"Full write successed"<<std::endl;
        return true;
    }
    std::cout<<"Full write failed!"<<std::endl;
    return false;
}


void Sender::disconnectSocket(int socketfd){
    close(socketfd);
}


















