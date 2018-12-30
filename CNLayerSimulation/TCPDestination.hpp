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
#include "cnformat.h"
#ifdef _socket_
#include "_socket_.cpp"
#endif

// Destination class
class Destination {
private:
    // Data:
    TCPAutomation currentState;
    Interface inter;
    TCPPackage tcpToStr(string str);
    // Function:
public:
    // Data:
    
    // Function:
    bool startReceive(void);
    // Constructors
    Destination () {};
};

#endif /* TCPDestination_hpp */
