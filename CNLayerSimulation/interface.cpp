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

bool Interface:: printValist(va_list ap, const char *fmt, int left = BUFFSIZE + 1) {
    char buf[BUFFSIZE], *p;
    
    vsnprintf(buf, BUFSIZ, fmt, ap);
    int length = static_cast<int>( strlen(buf) );
    if (left < length) {
        p = buf;
        int times = 0;
        for (int inter = left; inter <= length + left; inter += left) {
            char tmp = buf[inter];
            buf[inter] = 0;
            printf("%s", p);
            moveDown(1);
            moveLeft(left);
            buf[inter] = tmp;
            p += left;
            times++;
        }
    } else {
        printf("%s", buf);
    }
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
    printValist(ap, fmt, left);
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
    if (seg.title == edge.title) {
        moveToCommand();
    } else {
        moveToSegment(seg);
        moveDown(1);
        moveRight(1);
    }
    while((*(t++) = getchar()) != '\n') { }
    *(t-1) = 0;
    if (strcmp(input, "exit") == 0) {
        exit(0);
    }
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
        data.push_back(40);
    }
    inter.moveToCommand();
    return data;
}


bool ApplicationLayer:: writeEmail(string data) {
    vector<string> datas;
    int head = 0, i;
    for (i = 0; i < data.size(); i++) {
        if (data[i] == 40) {
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

static const int WIDTH_HEIGHT[4][2] = {
    0, 0,
    80, 4,
    64, 5,
    0, 0
};

string TITLES[6] = {
    "Explain Window",
    "Last Layer Data Window",
    "Constructing ... ",
    "--|Data|",
    "Head Window",
    "Tail Window",
};


bool LayerInterpret:: runIP() {
    ProcessIP ip;
    encapsulatedData = ip.encapsulate(dataFromLastLayer);
    explainItems = ip.interpret(encapsulatedData);
    return true;
}

bool LayerInterpret:: runTCP() {
    ProcessTCP tcp;
    encapsulatedData = tcp.encapsulate(dataFromLastLayer);
    explainItems = tcp.interpret(encapsulatedData);
    return true;
    
}

bool LayerInterpret:: interpret(string lastLayer) {
    dataFromLastLayer = lastLayer;
    switch (thisLayer) {
        case IP:
            runIP();
            break;
        case TCP:
            runTCP();
        default:
            break;
    }
    string cmd;
    inter.printAtSegment(windows[lastLayerWindow], 1, dataFromLastLayer.data());
    for (vector<DataFormat>::iterator it = explainItems.begin(); it < explainItems.end(); it++) {
        cmd = inter.getLine(inter.edge);
        if (cmd == ".") {
            break;
        }
        int x = it->indexOfField / trueWidth + 1;
        int y = it->indexOfField % trueWidth + 1;
        inter.printAtSegment(windows[infoWindow], 1, it->explainOfField.data());
        inter.printAtSegment(windows[headWindow], x, y, it->valueOfField.data());
    }
    inter.printAtSegment(windows[currentValueWindow], 1, (encapsulatedData.head+encapsulatedData.dataOfUpLayer+encapsulatedData.tail).data());
    return true;
}

LayerInterpret:: LayerInterpret(Layer l): thisLayer(l) {
    trueWidth = WIDTH_HEIGHT[thisLayer][0];
    trueHeight = WIDTH_HEIGHT[thisLayer][1];
    int leftOffset = 110 - FakeDataWidth - trueWidth - 4;
    Window tmp1(InfoBegin, LeftBegin, InfoWidth, InfoLines);
    windows.push_back(tmp1);
    
    Window tmp2(InfoBegin, InfoWidth + WidthOffset, InfoWidth, InfoLines);
    windows.push_back(tmp2);
    
    Window tmp3(InfoBegin + InfoLines + HeightOffset + trueHeight, LeftBegin, InfoWidth * 2, WholeDataLines);
    windows.push_back(tmp3);
    
    Window tmp4(InfoBegin + InfoLines + HeightOffset, trueWidth + leftOffset + 2, FakeDataWidth, trueHeight);
    windows.push_back(tmp4);
    
    Window tmp5(InfoBegin + InfoLines + HeightOffset, leftOffset, trueWidth + 2, trueHeight);
    windows.push_back(tmp5);
    
    // print lastLayerWindow to fakeDataWindow
    for (int i = 0; i < 4; i++) {
        inter.printAtSegment(inter.edge, 21 + i, 74 + i * 5, "\\");
        inter.printAtSegment(inter.edge, 21 + i, 135 - i * 8, "/");
    }
    
    // print board
    for (int i = 0; i < 5; i++) {
        windows[i].title = TITLES[i];
        inter.printBoard(windows[i]);
    }
    
    inter.printAtSegment(windows[fakeDataWindow], 1, "   D A T A");
}
