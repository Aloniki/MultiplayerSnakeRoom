//
//  JsonManager.cpp
//  GameServer
//
//  Created by Apple on 3/10/16.
//  Copyright © 2016 Aloniki's Study. All rights reserved.
//

#include "JsonManager.hpp"
using namespace rapidjson;

bool JsonManager::RoomInfoToJson(RoomInfo* ri, std::string& jRoomInfo){
    Document doc;
    Document::AllocatorType& allocator = doc.GetAllocator();
    
    Value jRoomID;
    jRoomID.SetInt(ri->getRoomID());
    
    Value jRoomAddr;
    auto cRoomAddr = ri->getRoomAddr().c_str();
    jRoomAddr.SetString(cRoomAddr, (int)(strlen(cRoomAddr)));
    
    Value jRoomHoster;
    auto cRoomHoster = ri->getRoomHoster().c_str();
    jRoomHoster.SetString(cRoomHoster, (int)(strlen(cRoomHoster)));
    
    Value root(kArrayType);
    root.PushBack(jRoomID, allocator).PushBack(jRoomAddr, allocator).PushBack(jRoomHoster, allocator);
    
    StringBuffer buffer;
    Writer<StringBuffer> writer(buffer);
    root.Accept(writer);
    
    std::string buf = buffer.GetString();
    jRoomInfo = buffer.GetString();
    //printf("aaaaaaaaa%s",buf.c_str());
    
    return false;
}


bool JsonManager::RoomListToJson(std::vector<RoomInfo>* source, std::string &destination){
    Document doc;
    Document::AllocatorType& allocator = doc.GetAllocator();
    
    Value root(kArrayType); //json entity array
    
    for (auto itor = source->begin(); itor != source->end(); itor++) {
        //convert the RoomInfo's fields to json type
        Value vid;
        vid.SetInt(itor->getRoomID());
        Value vaddr;
        vaddr.SetString(itor->getRoomAddr().c_str(),(int)(itor->getRoomAddr().length()));
        Value vhoster;
        vhoster.SetString(itor->getRoomHoster().c_str(), (int)(itor->getRoomHoster().length()));
        //convert the RoomInfo's entity to json type
        Value ventity(kObjectType);
        ventity.AddMember("id", vid, allocator).AddMember("addr", vaddr, allocator).AddMember("hoster", vhoster, allocator);
        //add to json entity array
        root.PushBack(ventity, allocator);
    }
    
    StringBuffer buffer;
    Writer<StringBuffer> writer(buffer);
    root.Accept(writer);
    auto rjson = buffer.GetString();
    
    destination = rjson;

    return true;
}










