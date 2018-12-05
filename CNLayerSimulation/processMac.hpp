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
    Data encapsulate(string fromUpLayer);
    Data disassemble(string currentLayerData);
    vector <DataFormat> interpret(Data);
};

#endif /* processMac_hpp */
