//
//  interface.hpp
//  NetworkLayerSimulation
//
//  Created by Max on 2018/12/5.
//  Copyright © 2018 Max. All rights reserved.
//

#ifndef interface_hpp
#define interface_hpp

#include <stdio.h>

#include "cnformat.h"
#include "processTCP.cpp"
#include "processIP.cpp"
#include "processMac.cpp"

// Interface class
class Interface {
public:
    // Data:
    // Function:
    bool moveToCommand(void);
    Interface () {}
};

#endif /* interface_hpp */
