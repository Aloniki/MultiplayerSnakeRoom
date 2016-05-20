//
//  RoomManager.hpp
//  GameRoom
//
//  Created by Apple on 5/7/16.
//  Copyright © 2016 Aloniki's Study. All rights reserved.
//

#ifndef PlayerStatusManager_hpp
#define PlayerStatusManager_hpp

#include <unistd.h>
#include "GameHeaders.h"
#include "PlayerStatus.hpp"

class RoomManager {
    static RoomManager* roomManager;
    
    RoomInfo* roomInfo;
    
    std::vector<PlayerStatus>* playerVector;  //contains all the players in this room
    
    RoomManager(){
        playerVector = new std::vector<PlayerStatus>();
    }
    
    ~RoomManager(){
        delete roomInfo;
        delete playerVector;
    }
public:
    static RoomManager* getRoomManager();
    
    std::vector<PlayerStatus>* getPlayerStatusList();
    
    RoomInfo* getRoomInfo();
    
    int getCurrentPlayerNumber();
    PlayerStatus* findPlayerByDescriptor(int);
    void addPlayer(PlayerStatus*);
    void removePlayer(long);
    
    void removePlayerFromRoom(int);
    
    bool isReady();
    
    void startGame();
    
};

#endif /* RoomManager_hpp */
