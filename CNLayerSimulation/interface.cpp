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

inline bool Interface:: setFontColor(int color) {
    printf("\033[%dm",(color));
    return true;
}

inline bool Interface:: setBackColor(int color) {
     printf("\033[%dm",(color));
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

bool Interface:: printAtSegment(Window seg, int x, int y, int color, const char *fmt, ...) {
    setBackColor(color);
    moveAt(seg, x, y);
    
    va_list ap;
    va_start(ap, fmt);
    printValist(ap, fmt);
    va_end(ap);
    
    moveToCommand();
    setBackColor(FRONT_WHITE);
    
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

string Interface:: getLine(Window seg, bool isPassWord = false) {
    char input[BUFFSIZE], *t = input;
    if (seg.title == edge.title) {
        moveToCommand();
    } else {
        moveToSegment(seg);
        moveDown(1);
        moveRight(1);
    }
    if (isPassWord) {
        system("stty -echo");
    }
    
    while((*(t++) = getchar()) != '\n') {}
    *(t-1) = 0;
    
    if (isPassWord) {
        system("stty echo");
    }
    
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

const string ApplicationLayer:: Titles[5] = {"To", "Cc", "Subject", "From", "Text"};
const int ApplicationLayer:: Places[5] = {3, 8, 13, 18, 23};
const int ApplicationLayer:: Lines[5] = {4, 4, 4, 4, 10};


string ApplicationLayer:: sendEmail(void) {
    string data;
    for (int i = 0; i < 5; i++) {
        data += (Titles[i] + ":" + inter.getLine(windows[i]));
        data.push_back(40);
    }
    inter.moveToCommand();
    return data;
}

bool ApplicationLayer:: writeEmail(string data) {
    vector<string> datas;
    int head = 0, i, times = 0;
    for (i = 0; i < data.size(); i++) {
        if (data[i] == 40) {
            string tmp = data.substr(head, i - head);
            tmp = tmp.substr(Titles[times].size() + 1, tmp.size() - Titles[times].size() + 1);
            times++;
            datas.push_back(tmp);
            head = i + 1;
        }
    }
    datas.push_back(data.substr(head, i - head));
    for (int i = 0; i < 5; i++) {
        inter.printAtSegment(windows[i], 1, datas[i].data());
    }
    return true;
}

ApplicationLayer:: ApplicationLayer () {
    for (int i = 0; i < 5; i++) {
        Window tmp(Places[i], LEFT_OFFSET, WIDTH, Lines[i], Titles[i]);
        windows.push_back(tmp);
        inter.printBoard(tmp);
    }
}

static const int WIDTH_HEIGHT[4][2] = {
    48, 5,
    80, 4,
    64, 5,
    0, 0
};

const string LayerInterpret:: TITLES[6] = {
    "Explain Window",
    "Up Layer Data Window",
    "Down Layer Data Window",
    "--|Data|",
    "Head Window",
    "Tail"
};


const string LayerInterpret:: Infos[5] = {
    "Datalink layer",
    "IP layer",
    "Transport layer",
    "Application"
    "Server"
};


bool LayerInterpret:: runIP(bool isFromUP = true) {
    ProcessIP ip;
    if (isFromUP) {
        encapsulatedData = ip.encapsulate(dataFromUpLayer);
    } else {
        encapsulatedData = ip.disassemble(dataFromDownLayer);
    }
    explainItems = ip.interpret(encapsulatedData);
    return true;
}

bool LayerInterpret:: runTCP(bool isFromUP = true) {
    ProcessTCP tcp;
    if (isFromUP) {
        encapsulatedData = tcp.encapsulate(dataFromUpLayer);
    } else {
        encapsulatedData = tcp.disassemble(dataFromDownLayer);
    }
    //encapsulatedData = tcp.encapsulate(dataFromUpLayer);
    explainItems = tcp.interpret(encapsulatedData);
    return true;
}

bool LayerInterpret:: runMac(bool isFromUP = true) {
    ProcessMac mac;
    if (isFromUP) {
        encapsulatedData = mac.encapsulate(dataFromUpLayer);
    } else {
        encapsulatedData = mac.disassemble(dataFromDownLayer);
    }
    //encapsulatedData = mac.encapsulate(dataFromUpLayer);
    explainItems = mac.interpret(encapsulatedData);
    return true;
}


bool LayerInterpret:: stop(int interval = 0) {
    string cmd;
    if (interval == 0) {
        cmd = inter.getLine(inter.edge);
        if (cmd == ".") {
            return false;
        }
    } else {
        fflush(stdout);
        sleep(interval);
    }
    return true;
}

bool LayerInterpret:: showTransmit(Layer from, Layer to, string data) {
    Window trans(10, 40, 40, 10, false);
    inter.printBoard(trans);
    
    inter.printAtSegment(trans, 1, ("Receive data from "+Infos[from]).data());
    inter.printAtSegment(trans, 2, ("Pass to "+Infos[to]).data());
    inter.printAtSegment(trans, 3, ("Received Data: " + data).data());
    
    return true;
}

bool LayerInterpret:: interpret(string lastLayer, int interval = 0, bool isFroTopToDown = true) {
    if (interval < 0) {
        return false;
    }
    if (isFroTopToDown) {
        dataFromUpLayer = lastLayer;
        inter.printAtSegment(windows[lastLayerWindow], 1, lastLayer.data());
    } else {
        dataFromDownLayer = lastLayer;
    }
    switch (thisLayer) {
        case Mac:
            runMac(isFroTopToDown);
            break;
        case IP:
            runIP(isFroTopToDown);
            break;
        case TCP:
            runTCP(isFroTopToDown);
        default:
            break;
    }
    if (stop()) {
        if (!isFroTopToDown) {
            inter.printAtSegment(windows[headWindow], 1, hexToBin(encapsulatedData.head).data());
            inter.printAtSegment(windows[currentValueWindow], 1, (encapsulatedData.head+encapsulatedData.dataOfUpLayer+encapsulatedData.tail).data());
        }
        int lastX = 1, lastY = 1;
        vector<DataFormat>::iterator itemsEnd = thisLayer == Mac ? explainItems.end() -1 : explainItems.end();
        for (vector<DataFormat>::iterator it = explainItems.begin(); it < itemsEnd; it++) {
            int x = it->indexOfField / trueWidth + 1;
            int y = it->indexOfField % trueWidth + 1;
            inter.printBoard(windows[infoWindow]);
            inter.printAtSegment(windows[infoWindow], 1, it->explainOfField.data());
            inter.printAtSegment(windows[headWindow], x, y, inter.FRONT_BLUE, it->valueOfField.data());
            if (it != explainItems.begin()) {
                inter.printAtSegment(windows[headWindow], lastX, lastY, (it-1)->valueOfField.data());
            }
            if (stop(interval) == false) {
                break;
            }
            lastX = x;
            lastY = y;
        }
        inter.printAtSegment(windows[headWindow], lastX, lastY, (itemsEnd-1)->valueOfField.data());
        if (thisLayer == Mac) {
            inter.printAtSegment(windows[tailWindow], 1, itemsEnd->valueOfField.data());
        }
    }
    if (isFroTopToDown) {
        inter.printAtSegment(windows[headWindow], 1, hexToBin(encapsulatedData.head).data());
        inter.printAtSegment(windows[currentValueWindow], 1, (encapsulatedData.head+encapsulatedData.dataOfUpLayer+encapsulatedData.tail).data());
        inter.printBoard(windows[lastLayerWindow]);
    } else {
        inter.printBoard(windows[headWindow]);
        inter.printAtSegment(windows[lastLayerWindow], 1, lastLayer.data());
        inter.printBoard(windows[currentValueWindow]);
    }
    stop(interval);
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
    
    if (thisLayer == Mac) {
        Window tail(InfoBegin + InfoLines + HeightOffset, trueWidth + leftOffset + FakeDataWidth + 4, WidthOfTail, trueHeight);
        windows.push_back(tail);
    }
    
    // print lastLayerWindow to fakeDataWindow
    for (int i = 0; i < 4; i++) {
        inter.printAtSegment(inter.edge, InfoLines + 3 + i, 74 + i * 5, "\\");
        inter.printAtSegment(inter.edge, InfoLines + 3 + i, 135 - i * 8, "/");
    }
    
    // print board
    for (int i = 0; i < windows.size(); i++) {
        windows[i].title = TITLES[i];
        inter.printBoard(windows[i]);
    }
    
    inter.printAtSegment(windows[fakeDataWindow], 1, "   D A T A");
}

// shell class

bool Shell:: welcomeWindow(void) {
    Window userWin(10, 60, 20, 4, false, "User");
    Window passWin(14, 60, 20, 4, false, "Password");
    Window typeWin(16, 60, 20, 4, false, "You are ?");
    
    inter.printBoard(userWin);
    inter.printBoard(passWin);
    inter.printBoard(typeWin);
    string username = inter.getLine(userWin);
    string password = inter.getLine(passWin, true);
    string typeString = inter.getLine(typeWin);
    
    if (typeString == "Server") {
        type = Server;
    } else {
        type = Client;
    }
    
    inter.printBoard(inter.edge);
    inter.printAtSegment(inter.edge, 10, 50, inter.FRONT_RED, "Log in successful!");
    
    return true;
}

bool Shell:: initialInfo(void) {
    basisInformation.desPort = 12345;
    basisInformation.srcPort = 12345;
    basisInformation.srcIP[0] = "172";
    basisInformation.srcIP[1] = "16";
    basisInformation.srcIP[2] = "100";
    basisInformation.srcIP[3] = "23";
    basisInformation.desIP[0] = "172";
    basisInformation.desIP[1] = "16";
    basisInformation.desIP[2] = "100";
    basisInformation.desIP[3] = "23";
    for (int i = 0; i < 6; i++) {
        basisInformation.srcMac[i].push_back('0' + rand() % 10);
        basisInformation.desMac[i].push_back('0' + rand() % 10);
        basisInformation.srcMac[i].push_back('0' + rand() % 10);
        basisInformation.desMac[i].push_back('0' + rand() % 10);
    }
    inter.moveToCommand();
    cout << "automate? ";
    cin >> interval;
    return true;
}

bool Shell:: runServer(string msg = "") {
    EmailSocket server(type);
    string msgFromPhysics, email;
    
    inter.printBoard(inter.edge);
    inter.moveToCommand();
    
    fflush(stdout);
    
    
    // test
    
    LayerInterpret mac(Mac);
    mac.interpret(msg, 0, false);
    
    LayerInterpret ip(IP);
    ip.interpret(mac.encapsulatedData.dataOfUpLayer, 0, false);
    
    LayerInterpret tcp(TCP);
    tcp.interpret(ip.encapsulatedData.dataOfUpLayer, 0, false);
    
    // test
    
    
    
//
//    msgFromPhysics = server.run();
//    email = hexToStr(msgFromPhysics);
//
    ApplicationLayer receiveEmail;
    receiveEmail.writeEmail(hexToStr(tcp.encapsulatedData.dataOfUpLayer));
    
    return true;
}

bool Shell:: runClient(void) {
    EmailSocket client(type);
    string cmd, email, dataFromApplication;
    
    cmd = inter.getLine(inter.edge);
    
    ApplicationLayer emailClient;
    email = emailClient.sendEmail();
    dataFromApplication = strToHex(email);
    

    LayerInterpret tcp(TCP);
    tcp.interpret(dataFromApplication);

    LayerInterpret ip(IP);
    ip.interpret(tcp.encapsulatedData.head + tcp.encapsulatedData.dataOfUpLayer, interval);

    LayerInterpret mac(Mac);
    mac.interpret(ip.encapsulatedData.head + ip.encapsulatedData.dataOfUpLayer);
    
    //test
    runServer(mac.encapsulatedData.head + mac.encapsulatedData.dataOfUpLayer + mac.encapsulatedData.tail);
    
    client.run(dataFromApplication);
    
    return true;
}

bool Shell:: startShell() {
    if (type == Server) {
        return runServer();
    } else {
        return runClient();
    }
}
