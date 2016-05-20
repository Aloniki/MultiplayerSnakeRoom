//
//  PlayerStatus.hpp
//  GameRoom
//
//  Created by Apple on 5/7/16.
//  Copyright © 2016 Aloniki's Study. All rights reserved.
//

#ifndef PlayerStatus_hpp
#define PlayerStatus_hpp

#include <unistd.h>
#include <iostream>

/**
 *  the states of player which is in room
 */
enum PlayerState{
    PS_UNPREPARED   =       0,
    PS_PREPARED     =       1,
    PS_GAMING       =       2,
};
/**
 *  the states of player which is in room
 */
enum PlayerRole{
    HOST        =       1,
    GUEST       =       2,
};

struct PlayerStatus {
    long        playerDescriptor;
    std::string playerName;
    PlayerRole  playerRole;
    PlayerState playerState;
    
    PlayerStatus(){
        this->playerDescriptor = 0;
        this->playerName = "player";
        this->playerRole = PlayerRole::GUEST;
        this->playerState = PlayerState::PS_UNPREPARED;
    }
    
    PlayerStatus(std::string name, long descriptor, PlayerRole role){
        this->playerName = name;
        this->playerState = PlayerState::PS_UNPREPARED;
        this->playerDescriptor = descriptor;
        this->playerRole = role;
    }
    
    PlayerState getPlayerState(){return this->playerState;};
    void changePlayerState(PlayerState state){this->playerState = state;};
    
    long getPlayerDescriptor(){return this->playerDescriptor;};
};

#endif /* PlayerStatus_hpp */
