//
//  GameHeaders.h
//  GameClient
//
//  Created by Apple on 3/3/16.
//  Copyright © 2016 Aloniki's Study. All rights reserved.
//

#ifndef GameHeaders_h
#define GameHeaders_h

#include "DataPacketProtocol.hpp"
#include "JsonManager.hpp"
#include "errno.h"

//an unique port for each room that used to interact with client
static in_port_t IWCLIENTPORT;

#define ServIPAddr "127.0.0.1"
#define IBSCPort 9997
#define IBSRPort 9998
#define IBCRPort IWCLIENTPORT

#define MAXLINE         9999
#define LISTENQ         10
/**
 OperationSignalTypes----------string version
 */
//#define sEXIT            "EXIT"
//#define sREQUIRE         "REQUIRE"
//#define sCREATE          "CREATE"
//#define sJOIN            "JOIN"


#endif /* GameHeaders_h */