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
    
    //convert the RoomInfo's fields to json type
    Value vid;
    vid.SetInt(ri->getRoomID());
    Value vip;
    vip.SetString(ri->getRoomIP().c_str(),allocator);
    Value vport;
    vport.SetInt(ri->getRoomPort());
    Value vstate;
    vstate.SetInt(ri->getRoomState());
    Value vroomName;
    vroomName.SetString(ri->getRoomName().c_str(), allocator);
    Value vhost;
    vhost.SetString(ri->getRoomHost().c_str(), allocator);
    Value vMaxPlayers;
    vMaxPlayers.SetInt((int)ri->getMaxplayers());
    Value vCurrentPlayers;
    vCurrentPlayers.SetInt((int)ri->getCurrentPlayers());
    //convert the RoomInfo's entity to json type
    Value ventity(kObjectType);
    ventity.AddMember("id", vid, allocator).AddMember("ip", vip, allocator).AddMember("port", vport, allocator).AddMember("state", vstate, allocator).AddMember("roomName", vroomName, allocator).AddMember("host", vhost, allocator).AddMember("maxPlayers", vMaxPlayers, allocator).AddMember("currentPlayers", vCurrentPlayers, allocator);
    //add to json entity array
    
    StringBuffer buffer;
    Writer<StringBuffer> writer(buffer);
    ventity.Accept(writer);
    
    std::string buf = buffer.GetString();
    jRoomInfo = buffer.GetString();
    //printf("aaaaaaaaa%s",buf.c_str());
    
    return true;
}


bool JsonManager::RoomListToJson(std::vector<RoomInfo>* source, std::string &destination){
    Document doc;
    Document::AllocatorType& allocator = doc.GetAllocator();
    
    Value root(kArrayType); //json entity array
    
    for (auto itor = source->begin(); itor != source->end(); itor++) {
        //convert the RoomInfo's fields to json type
        Value vid;
        vid.SetInt(itor->getRoomID());
        Value vip(kStringType);
        vip.SetString(itor->getRoomIP().c_str(), allocator);
        Value vport;
        vport.SetInt(itor->getRoomPort());
        Value vstate;
        vstate.SetInt(itor->getRoomState());
        Value vroomName;
        vroomName.SetString(itor->getRoomName().c_str(), allocator);
        Value vhost(kStringType);
        vhost.SetString(itor->getRoomHost().c_str(), allocator);
        Value vMaxPlayers;
        vMaxPlayers.SetInt((int)itor->getMaxplayers());
        Value vCurrentPlayers;
        vCurrentPlayers.SetInt((int)itor->getCurrentPlayers());
        //convert the RoomInfo's entity to json type
        Value ventity(kObjectType);
        ventity.AddMember("id", vid, allocator).AddMember("ip", vip, allocator).AddMember("port", vport, allocator).AddMember("state", vstate, allocator).AddMember("roomName", vroomName, allocator).AddMember("host", vhost, allocator).AddMember("maxPlayers", vMaxPlayers, allocator).AddMember("currentPlayers", vCurrentPlayers, allocator);
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

bool JsonManager::JsonToRoomInfo(std::string& jRoomInfo, RoomInfo& roomInfo){
    Document doc;
//    Document::AllocatorType& allocator = doc.GetAllocator();
    
    doc.Parse(jRoomInfo.c_str());
    auto ri = doc.GetObject();
    
    auto itorID = ri.FindMember("id");
    roomInfo.setRoomID(itorID->value.GetInt());
    
    auto itorIP = ri.FindMember("ip");
    roomInfo.setRoomIP(itorIP->value.GetString());
    
    auto itorPort = ri.FindMember("port");
    roomInfo.setRoomPort(itorPort->value.GetInt());
    
    auto itorState = ri.FindMember("state");
    roomInfo.setRoomState((RoomState)(itorState->value.GetInt()));
    
    auto itorRoomName = ri.FindMember("roomName");
    roomInfo.setRoomName(itorRoomName->value.GetString());
    
    auto itorHost = ri.FindMember("host");
    roomInfo.setRoomHost(itorHost->value.GetString());
    
    auto itorMaxPlayers = ri.FindMember("maxPlayers");
    roomInfo.setMaxPlayers(itorMaxPlayers->value.GetInt());
    
    auto itorCurrentPlayers = ri.FindMember("currentPlayers");
    roomInfo.setCurrentPlayers(itorCurrentPlayers->value.GetInt());
    
    
//    for (auto itor = ri.begin(); itor != ri.end(); itor++) {
//        auto name = itor->name.GetString();
//        auto value = itor->value.GetString();
//        std::cout<<name<<":"<<std::endl;
//    }
    return true;
}

bool JsonManager::JsonToRoomSetting(std::string &jRoomSetting, RoomSetting &roomSetting){
    Document doc;
    
    doc.Parse(jRoomSetting.c_str());
    auto rs = doc.GetObject();
    
    auto itorRoomName = doc.FindMember("roomName");
    roomSetting.roomName = itorRoomName->value.GetString();
    auto itorMaxPlayers = doc.FindMember("maxPlayers");
    roomSetting.maxPlayers = itorMaxPlayers->value.GetInt();
    
    return true;
}

bool JsonManager::JsonToJoinedPlayerStatus(std::string &jPlayerStatus, PlayerStatus &playerStatus){
    Document doc;
    
    doc.Parse(jPlayerStatus.c_str());
    auto ps = doc.GetObject();
    
    auto itorPlayerDescriptor = doc.FindMember("playerDescriptor");
    playerStatus.playerDescriptor = itorPlayerDescriptor->value.GetInt64();
    auto itorPlayerRole = doc.FindMember("playerRole");
    playerStatus.playerRole = (PlayerRole)itorPlayerRole->value.GetInt();
    auto itorPlayerName = doc.FindMember("playerName");
    playerStatus.playerName = itorPlayerName->value.GetString();
    auto itorPlayerState = doc.FindMember("playerState");
    playerStatus.playerState = (PlayerState)itorPlayerState->value.GetInt();
    
    
    return true;
}

bool JsonManager::PlayerStatusToJson(PlayerStatus *ps, std::string &jPlayerStatus){
    Document doc;
    Document::AllocatorType& allocator = doc.GetAllocator();
    
    //convert the RoomInfo's fields to json type
    Value vplayerDescriptor;
    vplayerDescriptor.SetInt64(ps->playerDescriptor);
    Value vplayerName;
    vplayerName.SetString(ps->playerName.c_str(),allocator);
    Value vplayerRole;
    vplayerRole.SetInt(ps->playerRole);
    Value vplayerState;
    vplayerState.SetInt(ps->playerState);
    //convert the RoomInfo's entity to json type
    Value ventity(kObjectType);
    ventity.AddMember("playerDescriptor", vplayerDescriptor, allocator).AddMember("playerName", vplayerName, allocator).AddMember("playerRole", vplayerRole, allocator).AddMember("playerState", vplayerState, allocator);
    
    StringBuffer buffer;
    Writer<StringBuffer> writer(buffer);
    ventity.Accept(writer);
    
    std::string buf = buffer.GetString();
    jPlayerStatus = buffer.GetString();
    //printf("aaaaaaaaa%s",buf.c_str());
    
    return true;
}

bool JsonManager::PlayerStatusListToJson(std::vector<PlayerStatus> *source, std::string &destination){
    Document doc;
    Document::AllocatorType& allocator = doc.GetAllocator();
    
    Value root(kArrayType); //json entity array
    
    for (auto itor = source->begin(); itor != source->end(); itor++) {
        //convert the RoomInfo's fields to json type
        Value vplayerDescriptor;
        vplayerDescriptor.SetInt64(itor->playerDescriptor);
        Value vplayerName;
        vplayerName.SetString(itor->playerName.c_str(),allocator);
        Value vplayerRole;
        vplayerRole.SetInt(itor->playerRole);
        Value vplayerState;
        vplayerState.SetInt(itor->playerState);
        //convert the RoomInfo's entity to json type
        Value ventity(kObjectType);
        ventity.AddMember("playerDescriptor", vplayerDescriptor, allocator).AddMember("playerName", vplayerName, allocator).AddMember("playerRole", vplayerRole, allocator).AddMember("playerState", vplayerState, allocator);
        //add to json entity array
        root.PushBack(ventity, allocator);
    }
    
    StringBuffer buffer;
    Writer<StringBuffer> writer(buffer);
    root.Accept(writer);
    
    std::string buf = buffer.GetString();
    destination = buffer.GetString();
    //printf("aaaaaaaaa%s",buf.c_str());
    
    return true;
}


























