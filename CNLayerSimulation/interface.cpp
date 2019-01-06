//
//  interface.cpp
//  NetworkLayerSimulation
//
//  Created by Max on 2018/12/5.
//  Copyright © 2018 Max. All rights reserved.
//

#include "interface.hpp"
const string ApplicationLayer:: Titles[6] = {"To", "Cc", "Subject", "From", "Text", "Accessory"};
const int ApplicationLayer:: Places[6] = {3, 8, 13, 18, 23, 29};
const int ApplicationLayer:: Lines[6] = {4, 4, 4, 4, 6, 3};

string Infos[5] = {"zzz@qq.com", "no", "A file", "maxhhk@outlook.com", "File"};

string ApplicationLayer:: sendEmail(void) {
    string data = "$$";
    for (int i = 0; i < 5; i++) {
        data += (inter.getLine(windows[i]) + "$$");
    }
    inter.moveToCommand();
    filePath = inter.getLine(windows[5]);
    return data;
}

bool ApplicationLayer:: writeEmail(string data, string filePath) {
    vector<string> datas;
    for (int i = 0; i < 5; i++) {
        inter.printAtSegment(windows[i], 1, Infos[i].data());
    }
    inter.printAtSegment(windows[5], 1, ("./" + filePath).data());
    return true;
}

ApplicationLayer:: ApplicationLayer () {
    for (int i = 0; i < 6; i++) {
        Window tmp(Places[i], LEFT_OFFSET, WIDTH, Lines[i], Titles[i]);
        windows.push_back(tmp);
        inter.printBoard(tmp);
    }
}

static const int WIDTH_HEIGHT[5][2] = {
    0, 0,
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

const string LayerInterpret:: Infos[6] = {
    "Physical layer",
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
        nextLayer = Mac;
    } else {
        encapsulatedData = ip.disassemble(dataFromDownLayer);
        nextLayer = TCP;
    }
    explainItems = ip.interpret(encapsulatedData);
    return true;
}

bool LayerInterpret:: runTCP(bool isFromUP = true) {
    ProcessTCP tcp;
    if (isFromUP) {
        encapsulatedData = tcp.encapsulate(dataFromUpLayer);
        nextLayer = IP;
    } else {
        encapsulatedData = tcp.disassemble(dataFromDownLayer);
        nextLayer = Application;
    }
    //encapsulatedData = tcp.encapsulate(dataFromUpLayer);
    explainItems = tcp.interpret(encapsulatedData);
    return true;
}

bool LayerInterpret:: runMac(bool isFromUP = true) {
    ProcessMac mac;
    if (isFromUP) {
        encapsulatedData = mac.encapsulate(dataFromUpLayer);
        nextLayer = Physics;
    } else {
        encapsulatedData = mac.disassemble(dataFromDownLayer);
        nextLayer = IP;
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
    } else if (interval == 10) {
        return true;
    } else {
        fflush(stdout);
        sleep(interval);
    }
    return true;
}

bool LayerInterpret:: showTransmit() {
    inter.printBoard(inter.edge);
    Window trans(10, 30, 70, 15, false);
    inter.printBoard(trans);
    
    inter.printAtSegment(trans, 1, ("Receive data from "+Infos[thisLayer]).data());
    inter.printAtSegment(trans, 2, ("Pass to "+Infos[nextLayer]).data());
    inter.printAtSegment(trans, 3, ("Pass Data: " + encapsulatedData.head + encapsulatedData.dataOfUpLayer + encapsulatedData.tail).data());
    
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
    showTransmit();
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
