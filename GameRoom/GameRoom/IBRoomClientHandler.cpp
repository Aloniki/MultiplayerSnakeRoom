//
//  IBRoomClientHandler.cpp
//  GameRoom
//
//  Created by Apple on 5/7/16.
//  Copyright © 2016 Aloniki's Study. All rights reserved.
//

#include "IBRoomClientHandler.hpp"

typedef void* (*tcb)(void*);

void runDetachedThread(tcb method, void* arg){
    pthread_t tid;
    pthread_attr_t attr;
    pthread_attr_init(&attr);
    pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);
    pthread_create(&tid, &attr, method, arg);
    pthread_attr_destroy(&attr);
}

void* sendUpdatedSignToAllPlayers(void* arg){
    auto vector = RoomManager::getRoomManager()->getPlayerStatusList();
    for (auto itor = vector->begin(); itor != vector->end(); itor++) {
        int descriptor = (int)itor->getPlayerDescriptor();
        
        std::string jPlayerList;
        JsonManager::PlayerStatusListToJson(RoomManager::getRoomManager()->getPlayerStatusList(), jPlayerList);
        auto updateSignal = DataPacketProtocol::Pack(ROOMROLE, R2CSignal::R2C_UPDATE, &jPlayerList);
        std::cout<<"send to all update:"<<updateSignal<<std::endl;
        FullWrite(descriptor, updateSignal);
    }
    pthread_exit(0);
}

void* askAllPlayersToStart(void* arg){
    auto vector = RoomManager::getRoomManager()->getPlayerStatusList();
    for (auto itor = vector->begin(); itor != vector->end(); itor++) {
        int descriptor = (int)itor->getPlayerDescriptor();
        auto startSignal = DataPacketProtocol::Pack(ROOMROLE, R2CSignal::R2C_GAMEWILLSTART);
        std::cout<<"all player will start! :"<<startSignal<<std::endl;
        FullWrite(descriptor, startSignal);
    }
    pthread_exit(0);
}

void* sendSignToServer(void* arg){
    int socketfd = Sender::connectToRole(SERVERROLE, IBSRPort);
    
    auto type = *((int*)arg);
    switch (type) {
        case R2SSignal::CLOSED: {
            
            break;
        }
        case R2SSignal::UPDATED: {
            Sender::send(SERVERROLE, socketfd, R2SSignal::UPDATED, RoomManager::getRoomManager()->getRoomInfo());
            break;
        }
        case R2SSignal::STARTED: {
            
            break;
        }
        default:
            break;
    }
    
    Sender::disconnectSocket(socketfd);
    delete (int*)arg;
    pthread_exit(0);
}


void IBRoomClientHandler::handle(){
    while (true) {
        switch (this->RM->getRoomInfo()->getRoomState()) {
            //while room state is preparing
            case RoomState::R_PREPARING:{
                if (this->packetQueue->empty()) {
                    //            pause();
                    continue;
                }
                
                auto packet = this->pickFromPacketQueue();
                switch (packet.type) {
                    case C2RSignal::C2R_LEAVE:{
                        this->RM->removePlayer(this->connectfd);
                        
                        auto roomInfo = this->RM->getRoomInfo();
                        roomInfo->setCurrentPlayers(this->RM->getPlayerStatusList()->size());
                        
                        
                        
                        std::string jPlayerList;
                        JsonManager::PlayerStatusListToJson(this->RM->getPlayerStatusList(), jPlayerList);

                        std::cout<<"player is removed! Update info:"<<jPlayerList<<std::endl;
                        
                        runDetachedThread(sendUpdatedSignToAllPlayers, this);
                        int* type = new int(R2SSignal::UPDATED);
                        runDetachedThread(sendSignToServer, type);
                        
                        goto stop;
                    }
                    case C2RSignal::C2R_JOIN:{
                        std::cout<<"a player join!"<<std::endl;
                        struct PlayerStatus playerStatus;
                        JsonManager::JsonToJoinedPlayerStatus(packet.rawStr, playerStatus);
                        playerStatus.playerDescriptor = this->connectfd;
                        std::cout<<"player status:"<<packet.rawStr<<std::endl;
                        this->RM->addPlayer(&playerStatus);
                        
                        auto roomInfo = this->RM->getRoomInfo();
                        roomInfo->setCurrentPlayers(this->RM->getPlayerStatusList()->size());
                        
                        std::string jPlayerList;
                        JsonManager::PlayerStatusListToJson(RoomManager::getRoomManager()->getPlayerStatusList(), jPlayerList);
                        auto joinedSignal = DataPacketProtocol::Pack(SERVERROLE, R2CSignal::R2C_JOINED, &jPlayerList);
                        std::cout<<"joined signal:"<<joinedSignal<<std::endl;
                        FullWrite(this->connectfd, joinedSignal);
                        
                        runDetachedThread(sendUpdatedSignToAllPlayers, this);
                        int* type = new int(R2SSignal::UPDATED);
                        runDetachedThread(sendSignToServer, type);
                        break;
                    }
                    case C2RSignal::C2R_PREPARE:{
                        auto playerStatus =  this->RM->findPlayerByDescriptor(this->connectfd);
                        playerStatus->playerState = PS_PREPARED;
                        
                        std::string jPlayerList;
                        JsonManager::PlayerStatusListToJson(RoomManager::getRoomManager()->getPlayerStatusList(), jPlayerList);
                        auto updateSignal = DataPacketProtocol::Pack(SERVERROLE, R2CSignal::R2C_UPDATE, &jPlayerList);
                        std::cout<<"player is prepared!! Update info:"<<updateSignal<<std::endl;
                        FullWrite(this->connectfd, updateSignal);

                        runDetachedThread(sendUpdatedSignToAllPlayers, this);
                        
                        if (this->RM->isReady()) {
                            runDetachedThread(askAllPlayersToStart, this);
                            int* type = new int(R2SSignal::UPDATED);
                            runDetachedThread(sendSignToServer, type);
                        }
                        break;
                    }
                    case C2RSignal::C2R_UNPREPARE:{
                        auto playerStatus =  this->RM->findPlayerByDescriptor(this->connectfd);
                        playerStatus->playerState = PS_UNPREPARED;
                        
                        std::string jPlayerList;
                        JsonManager::PlayerStatusListToJson(RoomManager::getRoomManager()->getPlayerStatusList(), jPlayerList);
                        auto updateSignal = DataPacketProtocol::Pack(SERVERROLE, R2CSignal::R2C_UPDATE, &jPlayerList);
                        std::cout<<"player is unprepared!! Update info:"<<updateSignal<<std::endl;
                        FullWrite(this->connectfd, updateSignal);
                        
                        runDetachedThread(sendUpdatedSignToAllPlayers, this);
                        
                        break;
                    }
                        
                    default:
                        break;
                }
                break;
            }
            //while room state is gaming
            case RoomState::R_GAMING:
                //
                break;
                
            default:
                break;
        }
    }
stop:
    std::cout<<"Room handler: I am stopped now!"<<std::endl;
}










