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
 Operation Types
 */
enum C2SSignal{
    INVALID     =  -1,
    EXIT        =   0,
    REQUIRE     =   1,
    CREATE      =   2,
    JOIN        =   3,
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
