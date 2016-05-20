//
//  FullWrite.cpp
//  GameRoom
//
//  Created by Apple on 5/10/16.
//  Copyright © 2016 Aloniki's Study. All rights reserved.
//

#include <unistd.h>
#include <iostream>

static bool FullWrite(int sockfd, std::string& packet){
    auto c_packet = packet.c_str();
    auto length = strlen(c_packet);
    auto wCount = 0;
    auto rCount = length;
    ssize_t n = 0;
    while (true) {
        n = write(sockfd, c_packet, rCount);
        if (-1 == n) {
            std::cout<<"error:"<<errno<<std::endl;
            close(sockfd);
            return false;
        }
        wCount += n;
        if (wCount >= length) {
            break;
        }
        c_packet += wCount;
        rCount -= wCount;
    }
    return true;
}