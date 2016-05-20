//
//  RoomSetting.hpp
//  GameServer
//
//  Created by Apple on 5/16/16.
//  Copyright © 2016 Aloniki's Study. All rights reserved.
//

#ifndef RoomSetting_hpp
#define RoomSetting_hpp

#include <unistd.h>
#include <iostream>

struct RoomSetting {
    std::string roomName;
    size_t maxPlayers;
};

#endif /* RoomSetting_hpp */
