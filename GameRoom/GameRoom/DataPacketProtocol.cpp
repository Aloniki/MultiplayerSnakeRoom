//
//  DataPacketProtocol.cpp
//  charstr
//
//  Created by Apple on 3/13/16.
//  Copyright © 2016 Aloniki's Study. All rights reserved.
//

#include "DataPacketProtocol.hpp"
#include <iostream>
using namespace std;

/**
 *  pack the raw data to formal data packet (with raw string)
 *
 *  @param role   who send these data
 *  @param type   what is the operation type
 *  @param rawStr the main content
 *
 *  @return a formal data packet string
 */
string DataPacketProtocol::Pack(int role, int type, std::string *rawStr){
    if (NULL != rawStr) {
        size_t length = rawStr->length() + PACKETHEADLENGTH;
        
        stringstream ss;
        //add the formal DATALENGTH part
        ss<<setw(DATALENGTH)<<setfill('0')<<length;
        //add the formal ROLE, TYPE part and raw string
        ss<<role<<type<<*rawStr;
        return ss.str();
    }else{
        cout<<"raw string cannot be NULL!"<<endl;
        return NULL;
    }
}
/**
 *  pack the raw data to formal data packet (without raw string)
 *
 *  @param role   who send these data
 *  @param type   what is the operation type
 *  @param rawStr the main content
 *
 *  @return a formal data packet string
 */
string DataPacketProtocol::Pack(int role, int type){
    size_t length = PACKETHEADLENGTH;
    
    stringstream ss;
    //add the formal DATALENGTH part
    ss<<setw(DATALENGTH)<<setfill('0')<<length;
    //add the formal ROLE, TYPE part and raw string
    ss<<role<<type;
    return ss.str();
}

/**
 *  unpack a formal data packet string to a data packet instance
 *
 *  @param dataPacket a formal data packet string
 *
 *  @return a data packet instance
 */
DataPacket DataPacketProtocol::Unpack(std::string *dataPacket){
    //get the raw string
    DataPacket packet;
    packet.role = dataPacket->at(DATALENGTH) - ASCIINUMOFFSET;
    packet.type = dataPacket->at(DATALENGTH + ROLELENGTH) -ASCIINUMOFFSET;
    packet.rawStr = dataPacket->substr(PACKETHEADLENGTH);
    
    return packet;
}