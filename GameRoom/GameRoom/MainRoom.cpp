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

#define SELFROLE ROOMROLE

ServerDaemon* iwClientServerDaemon;     //a server dameon that is interacting with client
ServerDaemon* iwServerClientDaemon;       //a client dameon that is interacting with server

//interaction thread IDs
pthread_t tidIWClient;
pthread_t tidIWServer;
   
/**
 Initialize server daemons
 
 - returns: void
 */
void init(const char* argv[]){
    IWCLIENTPORT = atoi(argv[1]); //get an unique port from startup args
    std::cout<<"port:"<<IBCRPort<<std::endl;
    iwClientServerDaemon = new ServerDaemon(CLIENTROLE);
    iwServerClientDaemon = new ServerDaemon(SERVERROLE);
    auto sender = Sender::getSender();
    sender->send(R2SSignal::CREATED);
}

/**
 *  run a new server daemon to interact with client
 *
 *  @param arg void
 *
 *  @return void
 */
void* interactWithClient(void* arg){
//    iwClientServerDaemon->run();
    pthread_exit(NULL);
}

/**
 *  run a new server daemon to interact with server
 *
 *  @param arg void
 *
 *  @return void
 */
void* interactWithServer(void* arg){
    iwServerClientDaemon->run();
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
    //create new threads to run server daemons
    pthread_create(&tidIWClient, NULL, interactWithClient, NULL);
    pthread_create(&tidIWServer, NULL, interactWithServer, NULL);
    //waiting for these threads
    pthread_join(tidIWClient, NULL);
    pthread_join(tidIWServer, NULL);
    //end this program
    exit(0);
}