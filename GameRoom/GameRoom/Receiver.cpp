//
//  Receiver.cpp
//  GameServer
//
//  Created by Apple on 4/13/16.
//  Copyright © 2016 Aloniki's Study. All rights reserved.
//

#include "Receiver.hpp"

void Receiver::receive(){
    /**
     *  解决接受粘包
     */
    while (true) {
        ssize_t readResult;                                 //the value of read return
        bzero(recv, MAXLINE);                                   //clear the receive buffer
        
        
        if (0 >= (readResult = read(this->connectfd, &recv, MAXLINE))){//read error handle
            if (EINTR == errno) {
                std::cout<<"ERROR: EINTR!!"<<std::endl;
            }
//            while (!this->packetList->empty()) {
//                DataPacket packet= this->packetList->front();
//                std::cout<<"packet:"<<packet.rawStr<<std::endl;
//                this->packetList->pop();
//            }
            close(connectfd);                               //close this socket connection
            break;
        }
        
        std::cout<<recv<<std::endl;
        
        strcat(buf, recv);                                  //copy to packet buffer
        recvCount += strlen(recv);
 
    PACKETSEPARATE://packet separate label
        if (DATALENGTH <= recvCount && 0 == packetLength) {          //get the packet length
            bzero(head, sizeof(head));
            strncpy(head, buf, DATALENGTH);
            packetLength = atoi(head);
        }
        if (0 < packetLength && recvCount == packetLength) {//get the complete packet
            std::string data = buf;
            this->addToPacketQueue(&data);
            
            std::cout<<"Complete Packet:"<<data<<std::endl;
            fflush(stdout);
            
            recvCount     = 0;
            packetLength  = 0;
            bzero(buf, 100);
        }else if (0 < packetLength && recvCount > packetLength){//more than a packet
            std::string raw   = buf;
            auto data  = raw.substr(0,packetLength);
            this->addToPacketQueue(&data);
            
            std::cout<<"Complete Packet:"<<data<<std::endl;
            fflush(stdout);
            
            auto next    = raw.substr(packetLength);
            recvCount   -= packetLength;
            packetLength = 0;
            bzero(buf, MAXLINE);
            strcpy(buf, next.c_str());
            
            if (DATALENGTH <= strlen(buf)) {//figures out reads sereval packets in a time
                goto PACKETSEPARATE;//if buffer may contain more entire packets, run again
            }
        }
    }
}

void Receiver::addToPacketQueue(std::string* data){
    DataPacket packet = DataPacketProtocol::Unpack(data);
    this->packetQueue->push(packet);
}



