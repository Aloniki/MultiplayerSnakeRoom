
//
//  IWSingleRoleThread.cpp
//  GameServer
//
//  Created by Apple on 4/13/16.
//  Copyright © 2016 Aloniki's Study. All rights reserved.
//

#include "IWSingleRoleThread.hpp"

/**
 *  thread recall wrappers, they are used to call true handle methods
 *
 *  @param arg this
 *
 *  @return void
 */
void* receiverThreadWrapper(void* arg){
    IWSingleRoleThread* pthis = (IWSingleRoleThread*)arg;
    pthis->runReceiver(NULL);
    pthread_exit(NULL);
}
void* handlerThreadWrapper(void* arg){
    IWSingleRoleThread* pthis = (IWSingleRoleThread*)arg;
    pthis->runHandler(NULL);
    pthread_exit(NULL);
}

/**
 *  create new threads to run receiver & handler
 */
void IWSingleRoleThread::run(){
    pthread_create(&tidReceiver, NULL, receiverThreadWrapper, this);
    pthread_create(&tidHandler, NULL, handlerThreadWrapper, this);
    
    pthread_join(tidReceiver, NULL);
    pthread_join(tidHandler, NULL);
}

/**
 *  run the receiver
 *
 *  @param arg void
 *
 *  @return void
 */
void* IWSingleRoleThread::runReceiver(void* arg){
    this->receiver->receive();
    return (void*)0;
}
/**
 *  run the handler
 *
 *  @param arg void
 *
 *  @return void
 */
void* IWSingleRoleThread::runHandler(void* arg){
    this->handler->handle();
    pthread_exit(NULL);
}









