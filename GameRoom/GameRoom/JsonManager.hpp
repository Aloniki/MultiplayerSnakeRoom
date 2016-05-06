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
#include "rapidjson/document.h"
#include "rapidjson/prettywriter.h"
#include "rapidjson/stringbuffer.h"
#include <vector>
#include <iostream>

class JsonManager{
public:
    static bool RoomInfoToJson(RoomInfo* ri, std::string& jRoomInfo);
    static bool RoomListToJson(std::vector<RoomInfo>* source, std::string& destination);
};

#endif /* JsonManager_hpp */
