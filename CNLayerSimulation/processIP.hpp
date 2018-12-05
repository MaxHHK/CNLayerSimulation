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
    Data encapsulate(string fromUpLayer);
    Data disassemble(string currentLayerData);
    vector <DataFormat> interpret(Data);
};

#endif /* processIP_hpp */
