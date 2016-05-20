//
//  PortManager.cpp
//  GameRoom
//
//  Created by Apple on 5/9/16.
//  Copyright © 2016 Aloniki's Study. All rights reserved.
//

#include "PortManager.hpp"
#include <iostream>

bool PortManager::isCanBind(in_port_t port){
    //establish socket
    auto listenfd = socket(AF_INET, SOCK_STREAM, 0);
    if (-1 == listenfd) {
        printf("socket establishment error!");
        return false;
    }
    
    struct sockaddr_in  servaddr;
    //init server address
    bzero(&servaddr,sizeof(servaddr));
    servaddr.sin_family         = AF_INET;
    servaddr.sin_addr.s_addr    = htonl(INADDR_ANY);
    servaddr.sin_port           = htons(port);
    
    //bind server address
    auto bindResult = bind(listenfd, (struct sockaddr*)&servaddr, sizeof(servaddr));
    close(listenfd);
    
    if (0 != bindResult) {
        std::cout<<"this port has been used! port:"<<port<<" error:"<<errno<<std::endl;
        return false;
    }else {
        std::cout<<"this port can use:"<<port<<std::endl;
        return true;
    }
}

in_port_t PortManager::getAvailablePort(){
    std::random_device rand;
    while (true) {
        auto rPort = MINIMALPORT + rand() % (MAXIMALPORT - MINIMALPORT);
        if (isCanBind(rPort)) {
            return rPort;
        }
    }
    return 0;
}
