//
//  cnformat.h
//  NetworkLayerSimulation
//
//  Created by Max on 2018/12/5.
//  Copyright © 2018 Max. All rights reserved.
//

#ifndef cnformat_h
#define cnformat_h

#include <string>
#include <vector>
#include <iostream>
#include <cstdlib>

#include "tool.cpp"
#include "Window.cpp"
#include "_socket_.cpp"

using namespace Tools;

using namespace std;

const int NumOfIP = 4;
const int NumOfMac = 6;
const int TTL = 255;

enum Layer {
    Physics,
    Mac,
    IP,
    TCP,
    Application,
    Others
};

struct Basic{
    string srcIP[NumOfIP];
    string desIP[NumOfIP];
    string srcMac[NumOfMac];
    string desMac[NumOfMac];
    int srcPort;
    int desPort;
    int TTL;
    Layer TransportLayer;
    Layer IPLayer;
    Layer DataLayer;
};

Basic basisInformation;

// interact with inferface
struct DataFormat {
    //
    Layer layer;
    int indexOfField;
    string valueOfField;
    string explainOfField;
};

struct Data {
    Layer layer;
    string head;
    string dataOfUpLayer;
    string tail;
};

// TCP stream structure
enum TCPFlags {
    URG,
    ACK,
    PSH,
    RST,
    SYN,
    FIN,
    IsTrue,
};

enum TCPAutomation {
    CLOSED, LISTEN, SYN_RCVD, SYN_SENT, ESTABLISHED, FIN_WAIT_1, FIN_WAIT_2, CLOSING, TIME_WAIT, CLOSE_WAIT, LAST_ACK,
};

struct TCPPackage {
    char flags[10];
    char sequence[10];
    char ask[10];
    int headLength;
    char checksum[17];
};


#endif /* cnformat_h */


