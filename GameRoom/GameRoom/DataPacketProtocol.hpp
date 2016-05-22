//
//  DataPacketProtocol.hpp
//  This file defines a data packet protocol, some macros and implementation methods.
//  Use these methods, you can do easily:
//      -packet raw data to a data packet;
//      -unpacket a data packet to raw data;
//
//  Created by Apple on 3/13/16.
//  Copyright © 2016 Aloniki's Study. All rights reserved.
//

#ifndef DataPacketProtocol_hpp
#define DataPacketProtocol_hpp

#include <string>
#include <cstring>
#include <sstream>
#include <iomanip>

//define length of different parts in the packet head
#define PACKETHEADLENGTH 6
#define DATALENGTH 4
#define ROLELENGTH 1
#define TYPELENGTH 1
//define roles
#define SERVERROLE 1
#define CLIENTROLE 2
#define ROOMROLE 4
#define STRINGTYPE 1
//define the offset of the char '0' to the num 0 in standard ASCII
#define ASCIINUMOFFSET 48

/**
 *  the states of player which is in room
 */
enum RoomPlayerRole{
    RR_HOST         = 1,
    RR_GUEST        = 2,
};

/**
 *  client to server signal types
 */
enum C2SSignal{
    C2S_INVALID     =  -1,
    C2S_EXIT        =   0,
    C2S_REQUIRE     =   1,
    C2S_CREATE      =   2,
};
/**
 *  server to client signal types
 */
enum S2CSignal{
    S2C_REQUIRED = 1,
    S2C_CREATED  = 2,
};
/**
 *  room to server signal types
 */
enum R2SSignal{
    CLOSED      =   0,
    CREATED     =   1,
    UPDATED     =   2,
    STARTED     =   3,
};
/**
 *  room to server signal types
 */
enum C2RSignal{
    C2R_LEAVE       =   0,
    C2R_JOIN        =   1,
    C2R_PREPARE     =   2,
    C2R_UNPREPARE   =   3,
};
/**
 *  room to client signal types
 */
enum R2CSignal{
    R2C_INVALID     = -1,
    R2C_JOINED      = 1,
    R2C_PREPARED    = 2,
    R2C_UNPREPARED  = 3,
    R2C_GAMEWILLSTART = 4,
    R2C_UPDATE      = 5,
    R2C_GAMEWILLSTOP = 6,
};
/**
 *  Use to record the role, type and raw string from a data packet
 */
struct DataPacket{
    int role;
    int type;
    std::string rawStr;
};

/**
 *  this class defines two static methods to pack raw data or unpack to data packets
 */
class DataPacketProtocol{
public:
    static std::string Pack(int role, int type, std::string* rawStr);
    static std::string Pack(int role, int type);
    static DataPacket Unpack(std::string* dataPacket);
};














#endif /* DataPacketProtocol_hpp */
