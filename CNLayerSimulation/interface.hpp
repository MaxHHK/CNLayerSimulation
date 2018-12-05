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
#include <cstdio>
#include <cstdarg>

#include "cnformat.h"
#include "processTCP.cpp"
#include "processIP.cpp"
#include "processMac.cpp"

struct Segment {
    int x, y;
    int width, height;
    Segment(int x, int y, int w, int h): x(x), y(y), width(w), height(h) {}
};

// Interface class
class Interface {
    // data
    static const int BUFFSIZE = 1024;
    static const int MAX_WIDTH  = 150;
    static const int MAX_HEIGHT = 38;
    // move cursor up, down left and right
    bool moveUp(int);
    bool moveDown(int);
    bool moveLeft(int);
    bool moveRight(int);
    bool resetCursor(void);
    bool moveAt(Segment, int, int);
    bool moveToSegment(Segment);
    bool printLine(char, int);
    bool printValist(va_list ap, const char *fmt);
public:
    // Data:
    // Function:
    bool clearSegment(Segment);
    bool printBoard(Segment);
    bool printAtSegment(Segment, int, const char *, ...);
    bool printAtSegment(Segment, int, int, const char *, ...);
    bool moveToCommand(void);
    Interface ();
};

#endif /* interface_hpp */
