//
//  interface.cpp
//  NetworkLayerSimulation
//
//  Created by Max on 2018/12/5.
//  Copyright © 2018 Max. All rights reserved.
//

#include "interface.hpp"

inline bool Interface:: moveUp(int x) {
    printf("\033[%dA", x);
    return true;
}

inline bool Interface:: moveDown(int x) {
    printf("\033[%dB", x);
    return true;
}

inline bool Interface:: moveLeft(int x) {
    printf("\033[%dD", x);
    return true;
}

inline bool Interface:: moveRight(int x) {
    printf("\033[%dC", (x));
    return true;
}

inline bool Interface:: resetCursor() {
    printf("\033[H");
    return true;
}

bool Interface:: moveAt(Segment seg, int x, int y) {
    moveToSegment(seg);
    moveDown(x);
    moveRight(y + 2);
    return true;
}

inline bool Interface:: moveToSegment(Segment seg) {
    resetCursor();
    moveDown(seg.x);
    moveRight(seg.y);
    return true;
}

bool Interface:: printLine(char c, int length) {
    for (int i = 0; i < length; i++) {
        putchar(c);
    }
    return true;
}

bool Interface:: printValist(va_list ap, const char *fmt) {
    char buf[BUFFSIZE];
    
    vsnprintf(buf, BUFSIZ, fmt, ap);
    printf("%s", buf);
    return true;
}


bool Interface:: clearSegment(Segment seg) {
    moveToSegment(seg);
    for (int i = 0; i < seg.height; i++) {
        printLine(' ', seg.width);
        moveDown(1);
    }
    return true;
}

bool Interface:: printBoard(Segment seg) {
    clearSegment(seg);
    moveToSegment(seg);
    printLine('-', seg.width);
    moveLeft(seg.width);
    for (int i = 1; i < seg.height - 2; i++) {
        moveDown(1);
        printf("%2d|", i);
        printLine(' ', seg.width - 4);
        putchar('|');
        moveLeft(seg.width);
    }
    moveDown(1);
    printLine('-', seg.width);
    moveDown(1);
    moveToCommand();
    return true;
}

bool Interface:: printAtSegment(Segment seg, int line, const char *fmt, ...) {
    moveAt(seg, line, 1);
    for (int i = 0; i < seg.width - 2; i++) {
        printf(" ");
    }
    moveLeft(seg.width - 2);
    
    va_list ap;
    va_start(ap, fmt);
    printValist(ap, fmt);
    va_end(ap);
    
    moveToCommand();
    
    return true;
}

bool Interface:: printAtSegment(Segment seg, int x, int y, const char *fmt, ...) {
    moveAt(seg, x, y);
    
    va_list ap;
    va_start(ap, fmt);
    printValist(ap, fmt);
    va_end(ap);
    
    moveToCommand();
    
    return true;
}

bool Interface:: moveToCommand(void) {
    resetCursor();
    moveDown(MAX_HEIGHT - 1);
    putchar('|');
    printLine(' ', MAX_WIDTH - 2);
    putchar('|');
    moveLeft(MAX_WIDTH);
    moveUp(1);
    putchar('|');
    printLine(' ', MAX_WIDTH - 2);
    putchar('|');
    moveLeft(MAX_WIDTH - 1);
    printf("$ ");
    return true;
}

Interface:: Interface() {
    system("clear");
    printLine('-', MAX_WIDTH);
    moveLeft(MAX_WIDTH);
    for (int i = 1; i < MAX_HEIGHT; i++) {
        moveDown(1);
        putchar('|');
        printLine(' ', MAX_WIDTH - 2);
        putchar('|');
        moveLeft(MAX_WIDTH);
    }
    moveUp(2);
    printLine('-', MAX_WIDTH);
    moveLeft(MAX_WIDTH);
    moveDown(3);
    printLine('-', MAX_WIDTH);
    moveToCommand();
}
