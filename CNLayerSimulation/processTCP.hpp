//
//  processTCP.hpp
//  NetworkLayerSimulation
//

#ifndef processTCP_hpp
#define processTCP_hpp

#include <stdio.h>

#include "cnformat.h"

class ProcessTCP {
    // Data
public:
    // function
    Data encapsulate(const string fromUpLayer);
    Data disassemble(const string currentLayerData);
    vector <DataFormat> interpret(const Data);
};

#endif /* processTCP_hpp */
