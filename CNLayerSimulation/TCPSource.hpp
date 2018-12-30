//
//  TCPSource.hpp
//  CNLayerSimulation
//
//  Created by Max on 2018/12/30.
//  Copyright © 2018 Max. All rights reserved.
//

#ifndef TCPSource_hpp
#define TCPSource_hpp

#include "cnformat.h"
#include <fcntl.h>

#ifdef _socket_
    #include "_socket_.cpp"
#endif

// Source class
class Source {
private:
    // Data:
    TCPAutomation currentState;
    int fileOffset;
    int sequence;
    int ack, window, length;
    int fileLength;
    bool Flags[4];
    Interface inter;
    static const string StateInfos[4];
    // Function:
    bool mySleep(int ms);
    bool setFlags(int, int, int, int);
    string makeTcp(int win, int len);
    bool dealTcp(string tcp);
    TCPPackage strToTcp(char *str);
    string tcpToStr(TCPPackage msg);
    bool sendMsg(string msg);
    string recvMsg(void);
    bool sendFile(string filePath);
    public:
    // Data:
    
    // Function:
    bool startSend(string filePath);
    bool connect();
    bool disconnect();
    // Constructors
    Source ();
};

#endif /* TCPSource_hpp */
