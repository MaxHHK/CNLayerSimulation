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

struct Window {
    bool withNum;
    int x, y;
    int width, height;
    string title;
    Window() {}
    Window(int x, int y, int w, int h, string head = ""): x(x), y(y), width(w), height(h), title(head) {
        withNum = false;
        head.clear();
    }
    Window(int x, int y, int w, int h, bool with, string head = ""): x(x), y(y), width(w), height(h), withNum(with), title(head) {}
};

// Interface class
class Interface {
    // data
    static const int BUFFSIZE = 1024;
    static const int MAX_WIDTH  = 150;
    static const int MAX_HEIGHT = 38;
    static const Window edge;
    // move cursor up, down left and right
    bool moveUp(int);
    bool moveDown(int);
    bool moveLeft(int);
    bool moveRight(int);
    bool resetCursor(void);
    bool moveToSegment(Window);
    bool printLine(char, int);
    bool printValist(va_list ap, const char *fmt);
    bool printEdge(void);
public:
    // Data:
    // Function:
    bool clearSegment(Window);
    bool printBoard(Window);
    bool printAtSegment(Window, int, const char *, ...);
    bool printAtSegment(Window, int, int, const char *, ...);
    bool moveToCommand(void);
    bool moveAt(Window, int, int);
    string getLine(Window);
    Interface ();
};

// ApplicationLayer class
class ApplicationLayer {
private:
    // Data:
    static const string Titles[4];
    static const int Places[4];
    static const int Lines[4];
    static const int INTER = 3;
    static const int LEFT_OFFSET = 25;
    static const int WIDTH = 90;
    Interface inter;
    vector<Window> windows;
    // Function:
public:
    // Data:
    
    // Function:
    // Constructors
    string sendEmail(void);
    bool writeEmail(string);
    ApplicationLayer ();
};

enum LayerWindows {
    infoLayer,
    lastLayer,
    currentValue,
    head,
    tail,
};

// IPLayer class
class IPLayer {
private:
    // Data:
    Interface inter;
    ProcessIP process;
    vector<Window> windows;
    // Function:
public:
    // Data:
    
    // Function:
    // Constructors
    IPLayer ();
};

#endif /* interface_hpp */
