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
    Data encapsulate(string fromUpLayer);
    Data disassemble(string currentLayerData);
    vector <DataFormat> interpret(Data);
};

#endif /* processTCP_hpp */
