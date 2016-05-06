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

#include <string>
#include <cstring>
#include "rapidjson/prettywriter.h"
#include "rapidjson/stringbuffer.h"
#include "rapidjson/schema.h"

class RoomInfo{
private:
    roomID_t roomID;
    std::string roomAddr;
    std::string roomHoster;
    
public:
    RoomInfo(int id,std::string addr, std::string hoster){
        this->roomID = id;
        this->roomAddr = addr;
        this->roomHoster = hoster;
    }
    
    roomID_t getRoomID();
    std::string getRoomAddr();
    std::string getRoomHoster();
    
    void setRoomID(roomID_t id);
    void setRoomAddr(std::string addr);
    void setRoomHoster(std::string hoster);
    void updateRoomInfo(RoomInfo*);
};

#endif /* RoomInfo_hpp */
