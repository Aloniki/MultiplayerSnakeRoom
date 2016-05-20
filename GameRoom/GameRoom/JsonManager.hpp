//
//  JsonManager.hpp
//  GameServer
//
//  Created by Apple on 3/10/16.
//  Copyright © 2016 Aloniki's Study. All rights reserved.
//

#ifndef JsonManager_hpp
#define JsonManager_hpp

#include "RoomInfo.hpp"
#include "RoomSetting.hpp"
#include "PlayerStatus.hpp"
#include "rapidjson/document.h"
#include "rapidjson/prettywriter.h"
#include "rapidjson/stringbuffer.h"
#include <vector>
#include <iostream>

class JsonManager{
public:
    static bool RoomInfoToJson(RoomInfo* ri, std::string& jRoomInfo);
    static bool RoomListToJson(std::vector<RoomInfo>* source, std::string& destination);
    static bool PlayerStatusToJson(PlayerStatus* ps, std::string& jPlayerStatus);
    static bool PlayerStatusListToJson(std::vector<PlayerStatus>* source, std::string& destination);
    
    static bool JsonToRoomInfo(std::string& jRoomInfo, RoomInfo& ri);
    static bool JsonToRoomSetting(std::string& jRoomSetting, RoomSetting& rs);
    static bool JsonToJoinedPlayerStatus(std::string& jPlayerStatus, PlayerStatus& ps);
};

#endif /* JsonManager_hpp */
