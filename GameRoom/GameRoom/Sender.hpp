//
//  Sender.hpp
//  GameRoom
//
//  Created by Apple on 5/6/16.
//  Copyright © 2016 Aloniki's Study. All rights reserved.
//

#ifndef Sender_hpp
#define Sender_hpp

#include <unistd.h>
#include <arpa/inet.h>
#include <pthread.h>
#include <iostream>
#include "GameHeaders.h"
#include "RoomManager.hpp"
#include "PortManager.hpp"

/**
 * this sender is connected to server, it is a single instance.
 */
class Sender {
public:
    static int connectToRole(int role, int port);
    static bool send(int role, int socketfd, int signal, void*data);
    static void disconnectSocket(int socketfd);
};

#endif /* Sender_hpp */
