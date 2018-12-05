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

const int MAX_WIDTH  = 150;
const int MAX_LENGTH = 40;

struct Segment {
    int x, y;
    int width, height;
};

// Interface class
class Interface {
public:
    // Data:
    // Function:
    bool printBoard(Segment);
    bool printAtSegment(Segment, const char *, ...);
    bool printAtSegment(Segment, int, int, const char *, ...);
    bool moveToCommand(void);
    Interface () {}
};

#endif /* interface_hpp */
