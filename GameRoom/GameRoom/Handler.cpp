//
//  Handler.cpp
//  GameServer
//
//  Created by Apple on 4/14/16.
//  Copyright © 2016 Aloniki's Study. All rights reserved.
//

#include "Handler.hpp"

/**
 *  pick the top data packet from the queue
 *
 *  @return return value description
 */
DataPacket Handler::pickFromPacketQueue(){
    auto packet = this->packetQueue->front();
    this->packetQueue->pop();
    return packet;
}