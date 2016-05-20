//
//  IBRoomClientHandler.cpp
//  GameRoom
//
//  Created by Apple on 5/7/16.
//  Copyright © 2016 Aloniki's Study. All rights reserved.
//

#include "IBRoomClientHandler.hpp"

void* sendSignToAllExceptOne(void* arg){
    auto pthis = (IBRoomClientHandler*)arg;
    pthis->sendToAll();
    pthread_exit(0);
}

void* sendSignToServer(void* arg){
    auto pthis = (IBRoomClientHandler*)arg;
    auto sender = Sender::getSender();
    
    sender->send(R2SSignal::UPDATED, RoomManager::getRoomManager()->getRoomInfo());
    pthread_exit(0);
}

void IBRoomClientHandler::sendToAll(){
    auto vector = this->RM->getPlayerStatusList();
    for (auto itor = vector->begin(); itor != vector->end(); itor++) {
        int descriptor = (int)itor->getPlayerDescriptor();
        
        std::string jPlayerList;
        JsonManager::PlayerStatusListToJson(RoomManager::getRoomManager()->getPlayerStatusList(), jPlayerList);
        auto updateSignal = DataPacketProtocol::Pack(SERVERROLE, R2CSignal::R2C_UPDATE, &jPlayerList);
        std::cout<<"send to all update:"<<updateSignal<<std::endl;
        FullWrite(descriptor, updateSignal);

    }
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
                        
                        pthread_t tid;
                        pthread_attr_t attr;
                        pthread_attr_init(&attr);
                        pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);
                        pthread_create(&tid, &attr, sendSignToAllExceptOne, this);
                        pthread_attr_destroy(&attr);
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
                        
                        pthread_t tid;
                        pthread_attr_t attr;
                        pthread_attr_init(&attr);
                        pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);
                        pthread_create(&tid, &attr, sendSignToAllExceptOne, this);
                        pthread_attr_destroy(&attr);
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

                        pthread_t tidToAll, tidToServer;
                        pthread_attr_t attrToAll, attrToServer;
                        pthread_attr_init(&attrToAll);
                        pthread_attr_init(&attrToServer);
                        pthread_attr_setdetachstate(&attrToAll, PTHREAD_CREATE_DETACHED);
                        pthread_attr_setdetachstate(&attrToServer, PTHREAD_CREATE_DETACHED);
                        pthread_create(&tidToAll, &attrToAll, sendSignToAllExceptOne, this);
                        pthread_create(&tidToServer, &attrToServer, sendSignToServer, this);
                        pthread_attr_destroy(&attrToAll);
                        pthread_attr_destroy(&attrToServer);
//                        if (this->RM->isReady()) {
//                            this->RM->startGame();
//                        }
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
                        
                        pthread_t tid;
                        pthread_attr_t attr;
                        pthread_attr_init(&attr);
                        pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);
                        pthread_create(&tid, &attr, sendSignToAllExceptOne, this);
                        pthread_attr_destroy(&attr);
                        
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










