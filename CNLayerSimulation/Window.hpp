//
//  Window.hpp
//  CNLayerSimulation
//
//  Created by Max on 2018/12/30.
//  Copyright © 2018 Max. All rights reserved.
//

#ifndef Window_hpp
#define Window_hpp

#include <stdio.h>
#include <cstdio>
#include <cstdio>
#include <cstdarg>

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
    // move cursor up, down left and right
    bool moveUp(int);
    bool moveDown(int);
    bool moveLeft(int);
    bool moveRight(int);
    bool resetCursor(void);
    bool moveToSegment(Window);
    bool printLine(char, int);
    bool printValist(va_list ap, const char *fmt, int);
    bool printEdge(void);
public:
    // Data:
    static const Window edge;
    // font color
    static const int  FRONT_BLACK = 30;
    static const int  FRONT_RED = 31;
    static const int  FRONT_GREEN = 32;
    static const int  FRONT_YELLOW = 33;
    static const int  FRONT_BLUE = 34;
    static const int  FRONT_PURPLE = 35;
    static const int  FRONT_DEEP_GREEN = 36;
    static const int  FRONT_WHITE = 37;
    // background color
    static const int  BACKGROUND_BLACK = 40;
    static const int  BACKGROUND_RED = 41;
    static const int  BACKGROUND_GREEN = 42;
    static const int  BACKGROUND_YELLOW = 43;
    static const int  BACKGROUND_BLUE = 44;
    static const int  BACKGROUND_PURPLE = 45;
    static const int  BACKGROUND_DEEP_GREEN = 46;
    static const int  BACKGROUND_WHITE = 47;
    // Function:
    bool setFontColor(int color);
    bool setBackColor(int color);
    bool clearSegment(Window);
    bool printBoard(Window);
    bool printAtSegment(Window, int, const char *, ...);
    bool printAtSegment(Window, int, int, const char *, ...);
    bool printAtSegment(Window, int, int, int, const char *, ...);
    bool moveToCommand(void);
    bool moveAt(Window, int, int);
    string getLine(Window, bool);
    Interface ();
};


#endif /* Window_hpp */
