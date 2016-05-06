//
//  RoomInfo.cpp
//  GameServer
//
//  Created by Apple on 3/7/16.
//  Copyright © 2016 Aloniki's Study. All rights reserved.
//

#include "RoomInfo.hpp"
#include "GameHeaders.h"
using namespace std;

/**
 *  Gets
 *
 *  @return class RoomInfo's fileds
 */
roomID_t RoomInfo::getRoomID(){
    return this->roomID;
}

string RoomInfo::getRoomAddr(){
    return this->roomAddr;
}

string RoomInfo::getRoomHoster(){
    return this->roomHoster;
}
/**
 *  Sets
 *
 *  @param id set the value of RoomInfo's fields
 */
void RoomInfo::setRoomID(roomID_t id){
    this->roomID   = id;
}

void RoomInfo::setRoomAddr(string addr){
    this->roomAddr = addr;
}

void RoomInfo::setRoomHoster(string hoster){
    this->roomHoster   = roomHoster;
}

void RoomInfo::updateRoomInfo(RoomInfo* roomInfo){
    this->roomID   = roomInfo->roomID;
    this->roomAddr = roomInfo->roomAddr;
    this->roomHoster   = roomInfo->roomHoster;
}


