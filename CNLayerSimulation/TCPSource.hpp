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

#ifdef _socket_
    #include "_socket_.cpp"
#endif

// Source class
class Source {
private:
    // Data:
    TCPAutomation currentState;
    int sequence;
    int ack;
    Interface inter;
    // Function:
public:
    // Data:
    
    // Function:
    bool startSend(string filePath);
    bool connect();
    // Constructors
    Source () {
        sequence = 1000;
        ack = 1000;
    };
};

#endif /* TCPSource_hpp */
