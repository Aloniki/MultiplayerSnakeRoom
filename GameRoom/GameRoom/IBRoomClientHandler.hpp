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
    
    static bool isPlayerCanCanclePrepare;
    static bool isStarting;
    static bool isFirstInit;
    
    pthread_mutex_t lock;
    
    //constructor
    IBRoomClientHandler(int fd, std::queue<DataPacket>* packetQueue) : Handler(fd, packetQueue){
        this->RM = RoomManager::getRoomManager();
        this->isPlayerCanCanclePrepare = true;
    }
    void handle();      //handle with clients
    
    bool getIsStarting();
    void stopStarting();
    void starting();
    
    void forbitCanclePrepare();
    void allowCanclePrepaer();
    bool getPermissionOfCanclePrepare();
};

#endif /* IBRoomClientHandler_hpp */
