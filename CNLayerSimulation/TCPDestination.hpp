//
//  TCPDestination.hpp
//  CNLayerSimulation
//
//  Created by Max on 2018/12/30.
//  Copyright © 2018 Max. All rights reserved.
//

#ifndef TCPDestination_hpp
#define TCPDestination_hpp

#include <stdio.h>
#include <stdlib.h>
#include "cnformat.h"
#ifdef _socket_
#include "_socket_.cpp"
#endif

enum FromOrTo {
    Fromsrc,
    Tosrc
};

enum exceptNum {
    normal,
    timeout,
    losspack
};

// Destination class
class Destination {
private:
    // Data:
    TCPAutomation currentState;
    // Interface inter;
    int portadd;
    int totalPacks;
    int Sequence;
    int Acknowage;
    int Window;
    int Len;
    int sourceSeq, sourceAck, sourceWin, sourceLen, mss;
    
    // Function:
    int seqs[20];
    int acks[20];
    int lens[20];
    int wins[20];
    FILE *file2;
public:
    // Data:
    
    // Function:
    string startReceive(const char* );
    void printStats(TCPAutomation);
    bool establishTcpConnection();
    bool releaseTcpConnection(const char* );
    bool mySleep(int );
    bool recvDatas(int );
    void sendmsg(const char* );
    int getNext(int , char* );
    string recvmsg();
    void printFunction(const char* , FromOrTo , bool, char*);
    void lossPackProc(int , int );
    void timeoutProc();
    // Constructors
    Destination();
};

#endif /* TCPDestination_hpp */
