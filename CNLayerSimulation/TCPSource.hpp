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
#include <vector>
#include <fstream>

#ifdef _socket_
#include "_socket_.cpp"
#include "tool.cpp"
#endif

// Source class

class Source {
private:
    // Data:
    static const string AlgoTypes[4];
    static const string StateInfos[4];
    static const string TCPAutoInfos[11];
    TCPAutomation currentState;
    
    int MSS, fileOffset, lastOffSet, fileSize, fd, dupFile, realMax;
    int sequence, ack, window, length, yourAck;
    int fileLength, timeInter, srcPort, desPort;
    int lines, cwnd, sendCwnd, ssthresh;
    bool debug;
    bool Flags[4], isCongest;
    string filePath, lastSendMsg, strOfWindows;
    vector<string> printInfos;
    ofstream debugFile;
    // Function:
    bool mySleep(int ms);
    bool setFlags(int, int, int, int);
    string makeTcp(int win, int len);
    bool dealTcp(string tcp);
    int dealSingleAck(string ack);
    TCPPackage strToTcp(char *str);
    string tcpToStr(TCPPackage msg);
    bool sendMsg(string msg);
    string recvMsg(void);
    bool sendFile();
    string encapsulateData();
    bool useAlgorithmSendTCP();
    int dealAllAcks(string allAcks);
    int slowStart(string allAcks);
    bool fastRetransimit(string allAcks, int numOfLast);
    bool outOfTime();
    vector<string> printAllTCPs(string, bool, bool);
    bool printSegment(string msg = "", bool isState = false);
    bool connect();
    bool disconnect();
public:
    // Data:
    
    // Function:
    bool startSend(string filePath);
    // Constructors
    Source ();
    ~Source () {
        debugFile.close();
    };
};

#endif /* TCPSource_hpp */
