//
//  interface.hpp
//  NetworkLayerSimulation
//
//  Created by Max on 2018/12/5.
//  Copyright © 2018 Max. All rights reserved.
//

#ifndef interface_hpp
#define interface_hpp

#include <cstdio>
#include <cstdio>
#include <cstdarg>

#include "cnformat.h"
#include "processTCP.cpp"
#include "processIP.cpp"
#include "processMac.cpp"

// ApplicationLayer class
class ApplicationLayer {
private:
    // Data:
    static const string Titles[6];
    static const int Places[6];
    static const int Lines[6];
    static const int INTER = 3;
    static const int LEFT_OFFSET = 25;
    static const int WIDTH = 90;
    Interface inter;
    vector<Window> windows;
    // Function:
public:
    // Data:
    string filePath;
    // Function:
    // Constructors
    string sendEmail(void);
    bool writeEmail(string, string);
    ApplicationLayer ();
};

enum LayerWindows {
    infoWindow = 0,
    lastLayerWindow = 1,
    currentValueWindow = 2,
    fakeDataWindow = 3,
    headWindow = 4,
    tailWindow = 5,
};

// IPLayer class
class LayerInterpret {
private:
    // Data:
    static const int InfoBegin = 3;
    static const int LeftBegin = 4;
    static const int InfoWidth = 65;
    static const int InfoLines = 13;
    static const int FakeDataWidth = 14;
    static const int WidthOffset = 8;
    static const int HeightOffset = 4;
    static const int WholeDataLines = 8;
    static const int WidthOfTail = 20;
    static const string TITLES[6];
    static const string Infos[6];
    int trueWidth;
    int trueHeight;
    string dataFromUpLayer;
    string dataFromDownLayer;
    vector<DataFormat> explainItems;
    Interface inter;
    ProcessIP process;
    vector<Window> windows;
    Layer thisLayer;
    Layer nextLayer;
    // Function:
    bool runIP(bool);
    bool runTCP(bool);
    bool runMac(bool);
    bool stop(int);
    bool showTransmit(void);
public:
    // Data:
    Data encapsulatedData;
    // Function:
    bool interpret(string, int, bool);
    // Constructors
    LayerInterpret (Layer);
};


#endif /* interface_hpp */
