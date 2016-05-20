//
//  RoomInfo.hpp
//  GameServer
//
//  Created by Apple on 3/7/16.
//  Copyright © 2016 Aloniki's Study. All rights reserved.
//

#ifndef RoomInfo_hpp
#define RoomInfo_hpp

typedef int roomID_t;

#include <iostream>

/**
 *  the states of room
 */
enum RoomState{
    R_PREPARING =       1,
    R_GAMING    =       2,
};

class RoomInfo{
private:
    roomID_t roomID;
    std::string roomIP;
    in_port_t   roomPort;
    std::string roomName;
    std::string roomHost;
    RoomState roomState;
    size_t  maxPlayers;
    size_t  currentPlayers;
    
public:
    RoomInfo(){
        this->roomID = 0;
        this->roomIP = "None";
        this->roomPort = 0;
        this->roomState = RoomState::R_PREPARING;
        this->roomName = "room";
        this->roomHost = "None";
        this->maxPlayers = 2;
        this->currentPlayers = 0;
    };
    RoomInfo(int id,std::string ip, in_port_t port, std::string name, std::string host, size_t maximum){
        this->roomID = id;
        this->roomIP = ip;
        this->roomPort = port;
        this->roomState = RoomState::R_PREPARING;
        this->roomName = name;
        this->roomHost = host;
        this->maxPlayers = maximum;
        this->currentPlayers = 0;
    }
    
    roomID_t getRoomID();
    std::string getRoomIP();
    in_port_t getRoomPort();
    std::string getRoomName();
    std::string getRoomHost();
    RoomState getRoomState();
    size_t getMaxplayers();
    size_t getCurrentPlayers();
    
    void setRoomID(roomID_t id);
    void setRoomIP(std::string ip);
    void setRoomPort(in_port_t);
    void setRoomName(std::string name);
    void setRoomHost(std::string hoster);
    void setRoomState(RoomState);
    void setMaxPlayers(size_t);
    void setCurrentPlayers(size_t);
    void updateRoomInfo(RoomInfo*);
};

#endif /* RoomInfo_hpp */
