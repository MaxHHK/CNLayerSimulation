//
//  cnformat.h
//  NetworkLayerSimulation
//
//  Created by Max on 2018/12/5.
//  Copyright © 2018 Max. All rights reserved.
//

#ifndef cnformat_h
#define cnformat_h

#include <string>
#include <vector>
#include <iostream>

using namespace std;

const int NumOfIP = 4;
const int NumOfMac = 6;
const int TTL = 255;

enum Layer {
    Mac,
    IP,
    TCP,
};

struct Basic{
    string srcIP[NumOfIP];
    string desIP[NumOfIP];
    string srcMac[NumOfMac];
    string desMac[NumOfMac];
    int srcPort;
    int desPort;
    const int TTL;
    Layer TransportLayer;
    Layer IPLayer;
    Layer DataLayer;
};

Basic basisInformation();

// interact with inferface
struct DataFormat {
    //
    Layer layer;
    int indexOfField;
    string valueOfField;
    string explainOfField;
};

struct Data {
    Layer layer;
    string head;
    string dataOfUpLayer;
    string tail;
};

#endif /* cnformat_h */
