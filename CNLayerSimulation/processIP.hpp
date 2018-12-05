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
    // function
    Data encapsulate(const string fromUpLayer);
    Data disassemble(const string currentLayerData);
    vector <DataFormat> interpret(const Data);
};

#endif /* processIP_hpp */
