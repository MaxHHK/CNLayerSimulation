//
//  interface.cpp
//  NetworkLayerSimulation
//
//  Created by Max on 2018/12/5.
//  Copyright © 2018 Max. All rights reserved.
//

#include "interface.hpp"

const Window Interface:: edge(0, -2, MAX_WIDTH, MAX_HEIGHT + 1, true, "Computer Network Course Degin");

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

bool Interface:: moveAt(Window seg, int x, int y) {
    moveToSegment(seg);
    moveDown(x);
    seg.withNum ? moveRight(y + 2) : moveRight(y);
    return true;
}

inline bool Interface:: moveToSegment(Window seg) {
    resetCursor();
    moveDown(seg.x + 1);
    moveRight(seg.y + 3);
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

bool Interface:: printEdge() {
    printBoard(edge);
    moveToSegment(edge);
    moveAt(edge, MAX_HEIGHT - 3, 1);
    printLine('-', MAX_WIDTH - 4);
    return true;
}

bool Interface:: clearSegment(Window seg) {
    moveToSegment(seg);
    for (int i = 0; i < seg.height; i++) {
        printLine(' ', seg.width);
        moveLeft(seg.width);
        moveDown(1);
    }
    return true;
}

bool Interface:: printBoard(Window seg) {
    clearSegment(seg);
    moveToSegment(seg);
    if (seg.title.length() > 0) {
        int first = (seg.width - static_cast<int>(seg.title.length())) / 2 - 2;
        int left = seg.width - first - static_cast<int>(seg.title.length());
        for (int i = 0; i < first; i++) {
            putchar('-');
        }
        cout << seg.title;
        for (int i = 0; i < left; i++) {
            putchar('-');
        }
    } else {
        printLine('-', seg.width);
    }
    moveLeft(seg.width);
    for (int i = 1; i < seg.height - 1; i++) {
        moveDown(1);
        if (seg.withNum) {
            printf("%2d|", i);
            printLine(' ', seg.width - 4);
        } else {
            putchar('|');
            printLine(' ', seg.width - 2);
        }
        putchar('|');
        moveLeft(seg.width);
    }
    moveDown(1);
    printLine('-', seg.width);
    moveDown(1);
    moveToCommand();
    return true;
}

bool Interface:: printAtSegment(Window seg, int line, const char *fmt, ...) {
    moveAt(seg, line, 1);
    int left = seg.withNum ? seg.width - 4 : seg.width - 2;
    for (int i = 0; i < left; i++) {
        printf(" ");
    }
    moveLeft(left);
    
    va_list ap;
    va_start(ap, fmt);
    printValist(ap, fmt);
    va_end(ap);
    
    moveToCommand();
    
    return true;
}

bool Interface:: printAtSegment(Window seg, int x, int y, const char *fmt, ...) {
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
    moveDown(MAX_HEIGHT);
    printf(" %d|", MAX_HEIGHT - 1);
    printLine(' ', MAX_WIDTH - 4);
    putchar('|');
    moveLeft(MAX_WIDTH);
    moveUp(1);
    printf("%d|$ ", MAX_HEIGHT - 2);
    printLine(' ', MAX_WIDTH - 6);
    putchar('|');
    moveLeft(MAX_WIDTH - 5);
    return true;
}

string Interface:: getLine(Window seg) {
    char input[BUFFSIZE], *t = input;
    moveToSegment(seg);
    moveDown(1);
    moveRight(1);
    while((*(t++) = getchar()) != '\n') { }
    *(t-1) = 0;
    return input;
}

Interface:: Interface() {
    system("clear");
    printEdge();
    moveToCommand();
}

const string ApplicationLayer:: Titles[4] = { "Subject", "To", "From", "Text"};
const int ApplicationLayer:: Places[4] = {3, 9, 14, 20};
const int ApplicationLayer:: Lines[4] = {5, 4, 4, 10};


string ApplicationLayer:: sendEmail(void) {
    string data;
    for (int i = 0; i < 4; i++) {
        data += inter.getLine(windows[i]);
        data.push_back(5);
    }
    inter.moveToCommand();
    return data;
}


bool ApplicationLayer:: writeEmail(string data) {
    vector<string> datas;
    int head = 0, i;
    for (i = 0; i < data.size(); i++) {
        if (data[i] == 5) {
            string tmp = data.substr(head, i - head);
            datas.push_back(tmp);
            head = i + 1;
        }
    }
    datas.push_back(data.substr(head, i - head));
    for (int i = 0; i < 4; i++) {
        inter.printAtSegment(windows[i], 1, datas[i].data());
    }
    return true;
}

ApplicationLayer:: ApplicationLayer () {
    for (int i = 0; i < 4; i++) {
        Window tmp(Places[i], LEFT_OFFSET, WIDTH, Lines[i], Titles[i]);
        windows.push_back(tmp);
        inter.printBoard(tmp);
    }
}
