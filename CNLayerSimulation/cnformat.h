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
    int TTL;
    Layer TransportLayer;
    Layer IPLayer;
    Layer DataLayer;
};

Basic basisInformation;

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

string hexToBin(string hex) {
    vector<string> ans;
    string strBin;
    for (string::iterator it = hex.begin(); it < hex.end(); it++) {
        string tmp;
        switch (*it) {
            case '0':
                tmp = "0000";
                break;
            case '1':
                tmp = "0001";
                break;
            case '2':
                tmp = "0010";
                break;
            case '3':
                tmp = "0011";
                break;
            case '4':
                tmp = "0100";
                break;
            case '5':
                tmp = "0101";
                break;
            case '6':
                tmp = "0110";
                break;
            case '7':
                tmp = "0111";
                break;
            case '8':
                tmp = "1000";
                break;
            case '9':
                tmp = "1001";
                break;
            case 'A':
            case 'a':
                tmp = "1010";
                break;
            case 'B':
            case 'b':
                tmp = "1011";
                break;
            case 'C':
            case 'c':
                tmp = "1100";
                break;
            case 'D':
            case 'd':
                tmp = "1101";
                break;
            case 'E':
            case 'e':
                tmp = "1110";
                break;
            case 'F':
            case 'f':
                tmp = "1111";
                break;
            default:
                break;
        }
        ans.push_back(tmp);
    }
    strBin.clear();
    for (vector<string>:: iterator it = ans.begin(); it < ans.end(); it++) {
        strBin = strBin + *it;
    }
    return strBin;
}

#endif /* cnformat_h */


