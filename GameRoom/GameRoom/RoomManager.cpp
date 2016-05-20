//
//  RoomManager.cpp
//  GameRoom
//
//  Created by Apple on 5/7/16.
//  Copyright © 2016 Aloniki's Study. All rights reserved.
//

#include "RoomManager.hpp"

RoomManager* RoomManager::roomManager;

RoomManager* RoomManager::getRoomManager(){
    if (NULL == roomManager) {
        roomManager = new RoomManager();
    }
    return roomManager;
}

std::vector<PlayerStatus>* RoomManager::getPlayerStatusList(){
    return this->playerVector;
}

RoomInfo* RoomManager::getRoomInfo(){
    if (NULL == this->roomInfo) {
        this->roomInfo = new RoomInfo();
    }
    return roomInfo;
}

int RoomManager::getCurrentPlayerNumber(){
    return this->playerVector->size();
}

PlayerStatus* RoomManager::findPlayerByDescriptor(int descriptor){
    for (auto itor = this->playerVector->begin(); itor != this->playerVector->end(); itor++) {
        if (descriptor == itor->getPlayerDescriptor()) {
            return &(*itor);
        }
    }
    return NULL;
}

void RoomManager::addPlayer(PlayerStatus* player){
    this->playerVector->push_back(*player);
}

void RoomManager::removePlayer(long descriptor){
    for (auto itor = this->playerVector->begin(); itor != this->playerVector->end(); itor++) {
        if (descriptor == itor->getPlayerDescriptor()) {
            this->playerVector->erase(itor);
            break;
        }
    }
}


void RoomManager::removePlayerFromRoom(int descriptor){
    size_t oldNum = this->roomInfo->getCurrentPlayers();
    this->roomInfo->setCurrentPlayers(oldNum - 1);
    removePlayer(descriptor);
}

bool RoomManager::isReady(){
    for (auto itor = this->playerVector->begin(); itor != this->playerVector->end(); itor++) {
        if (PlayerState::PS_UNPREPARED == itor->getPlayerState()) {
            return false;
        }
    }
    return true;
}

void RoomManager::startGame(){
    this->getRoomInfo()->setRoomState(RoomState::R_PREPARING);
}










