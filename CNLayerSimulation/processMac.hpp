//
//  processMac.hpp
//  NetworkLayerSimulation
//

#ifndef processMac_hpp
#define processMac_hpp

#include <stdio.h>

#include "cnformat.h"

class ProcessMac {
    // Data
public:
    string type;
    string FCS;
    string sourceMac;
    string destinationMac;
    
public:
    // function
    Data encapsulate(const string fromUpLayer);
    Data disassemble(const string currentLayerData);
    vector <DataFormat> interpret(const Data);
    string getFCS(string M,string P);
};

#endif /* processMac_hpp */
