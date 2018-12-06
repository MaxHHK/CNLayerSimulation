//
//  processIP.hpp
//  NetworkLayerSimulation
//

#ifndef processIP_hpp
#define processIP_hpp

#include <stdio.h>

#include "cnformat.h"

class ProcessIP {
    // Data
public:
    string version;
    string head_length;
    string differentiated_services;
    string total_length;
    string identification;
    string flag;
    string offset;
    string ttl;
    string protocol;
    string head_examination;
    string sourceIP;
    string destinationIP;
    
public:
    // function
    Data encapsulate(const string fromUpLayer);
    Data disassemble(const string currentLayerData);
    vector <DataFormat> interpret(const Data);
};

string transfer(string x,int length);
string bmoc_calculation(string a,string b);
#endif /* processIP_hpp */
