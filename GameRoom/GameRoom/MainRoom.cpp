//
//  main.cpp
//  GameRoom
//
//  Created by Apple on 5/5/16.
//  Copyright © 2016 Aloniki's Study. All rights reserved.
//

#include "GameHeaders.h"
#include "arpa/inet.h"
#include <pthread.h>
#include "JsonManager.hpp"
#include "ServerDaemon.hpp"
#include "Sender.hpp"
#include "RoomManager.hpp"
#include "PortManager.hpp"

#define SELFROLE ROOMROLE

ServerDaemon* iwClientServerDaemon;     //a server dameon that is interacting with client

Sender* sender = Sender::getSender();

RoomManager* roomManager = RoomManager::getRoomManager();

//interaction thread IDs
pthread_t tidIWClient;
pthread_t tidDestory;
   
/**
 Initialize server daemons
 
 - returns: void
 */
void init(const char* argv[]){
    IWCLIENTPORT = PortManager::getAvailablePort(); //get an available port
    std::cout<<"get room info now"<<std::endl;
    auto roomInfo = roomManager->getRoomInfo();  //get room info instance
    std::cout<<"set room id now"<<std::endl;
    roomInfo->setRoomID(atoi(argv[1]));
    std::cout<<"set room ip now"<<std::endl;
    roomInfo->setRoomIP(RoomIPAddr);
    std::cout<<"set room port now"<<std::endl;
    roomInfo->setRoomPort(IBCRPort);
    std::cout<<"set room name now"<<std::endl;
    roomInfo->setRoomName(argv[2]);         //set the host name
    std::cout<<"set room max players now"<<std::endl;
    roomInfo->setMaxPlayers(atoi(argv[3])); //set the maximum number of players
    std::cout<<"new R2C daemon now"<<std::endl;
    
    iwClientServerDaemon = new ServerDaemon(CLIENTROLE);    //run interacting daemon
    
    std::cout<<"get sender now"<<std::endl;
    //send a created signal to server
    sender = Sender::getSender();
    std::cout<<"sent created signal now"<<std::endl;
    sender->send(R2SSignal::CREATED, roomManager->getRoomInfo());
}

/**
 *  run a new server daemon to interact with client
 *
 *  @param arg void
 *
 *  @return void
 */
void* interactWithClient(void* arg){
    iwClientServerDaemon->run();
    pthread_exit(NULL);
}
/**
 *  run a thread to destory this room if no one joins this room within a certain period
 *
 *  @param arg void
 *
 *  @return void
 */
void* selfDestory(void* arg){
//    sleep(10);
//    if (0 == roomManager->getRoomInfo()->getCurrentPlayers()) {
//        auto id = roomManager->getRoomInfo()->getRoomID();
//        sender->send(R2SSignal::CLOSED, &id);
//        pthread_kill(tidIWClient, SIGKILL);
//        exit(0);
//    }
    pthread_exit(NULL);
}

/**
 *  main logic method
 *
 *  @param argc the number of startup args
 *  @param argv startup args
 *
 *  @return 0
 */
int main(int argc, const char * argv[]) {
    //initialize
    init(argv);
    //create new thread to run server daemons
    pthread_create(&tidIWClient, NULL, interactWithClient, NULL);
    //create a timer to destory
    pthread_create(&tidDestory, NULL, selfDestory, NULL);
    //waiting for this threads
    pthread_join(tidDestory, NULL);
    pthread_join(tidIWClient, NULL);
    //end this program
    
    exit(0);
}