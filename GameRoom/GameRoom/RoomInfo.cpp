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

string RoomInfo::getRoomIP(){
    return this->roomIP;
}

in_port_t RoomInfo::getRoomPort(){
    return this->roomPort;
}

string RoomInfo::getRoomName(){
    return this->roomName;
}

string RoomInfo::getRoomHost(){
    return this->roomHost;
}

RoomState RoomInfo::getRoomState(){
    return this->roomState;
}

size_t RoomInfo::getMaxplayers(){
    return this->maxPlayers;
}

size_t RoomInfo::getCurrentPlayers(){
    return this->currentPlayers;
}

/**
 *  Sets
 *
 *  @param id set the value of RoomInfo's fields
 */
void RoomInfo::setRoomID(roomID_t id){
    this->roomID   = id;
}

void RoomInfo::setRoomIP(string ip){
    this->roomIP = ip;
}

void RoomInfo::setRoomPort(in_port_t port){
    this->roomPort = port;
}

void RoomInfo::setRoomName(std::string name){
    this->roomName = name;
}

void RoomInfo::setRoomHost(string hoster){
    this->roomHost   = hoster;
}

void RoomInfo::setRoomState(RoomState state){
    this->roomState = state;
}

void RoomInfo::setMaxPlayers(size_t maximum){
    this->maxPlayers = maximum;
}

void RoomInfo::setCurrentPlayers(size_t current){
    this->currentPlayers = current;
}

void RoomInfo::updateRoomInfo(RoomInfo* roomInfo){
    this->roomID   = roomInfo->roomID;
    this->roomIP = roomInfo->roomIP;
    this->roomPort = roomInfo->roomPort;
    this->roomHost   = roomInfo->roomHost;
    this->roomState = roomInfo->roomState;
    this->maxPlayers = roomInfo->maxPlayers;
    this->currentPlayers = roomInfo->currentPlayers;
}











