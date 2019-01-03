//
//  Shell.hpp
//  CNLayerSimulation
//
//  Created by Max on 2018/12/30.
//  Copyright © 2018 Max. All rights reserved.
//

#ifndef Shell_hpp
#define Shell_hpp

#include "_socket_.hpp"
#include "interface.cpp"
#include "TCPSource.cpp"
#include "TCPDestination.cpp"

// Shell class
class Shell {
private:
    // Data:
    int interval;
    bool debug;
    Interface inter;
    SocketType type;
    // Function:
    bool welcomeWindow(void);
    bool initialInfo(void);
    bool runServer(string);
    bool runClient(void);
public:
    // Data:
    
    // Function:
    bool startShell();
    // Constructors
    Shell () {
        initialInfo();
        welcomeWindow();
        debug = false;
    };
};

#endif /* Shell_hpp */
