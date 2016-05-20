//
//  PortManager.hpp
//  GameRoom
//
//  Created by Apple on 5/9/16.
//  Copyright © 2016 Aloniki's Study. All rights reserved.
//

#ifndef PortManager_hpp
#define PortManager_hpp

#include <unistd.h>
#include <random>
#include <arpa/inet.h>
#include "GameHeaders.h"

class PortManager {
protected:
    static bool isCanBind(in_port_t);
public:
    static in_port_t getAvailablePort();
};

#endif /* PortManager_hpp */
