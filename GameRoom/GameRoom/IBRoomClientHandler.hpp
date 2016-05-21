//
//  IBRoomClientHandler.hpp
//  GameRoom
//
//  Created by Apple on 5/7/16.
//  Copyright © 2016 Aloniki's Study. All rights reserved.
//

#ifndef IBRoomClientHandler_hpp
#define IBRoomClientHandler_hpp

#include "Handler.hpp"
#include "RoomManager.hpp"
#include "Sender.hpp"

class IBRoomClientHandler : Handler {
    RoomManager* RM;
public:
    //constructor
    IBRoomClientHandler(int fd, std::queue<DataPacket>* packetQueue) : Handler(fd, packetQueue){
        this->RM = RoomManager::getRoomManager();
    }
    void handle();      //handle with clients
};

#endif /* IBRoomClientHandler_hpp */
