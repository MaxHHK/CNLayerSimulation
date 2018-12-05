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
    // function
    Data encapsulate(const string fromUpLayer);
    Data disassemble(const string currentLayerData);
    vector <DataFormat> interpret(const Data);
};

#endif /* processMac_hpp */
