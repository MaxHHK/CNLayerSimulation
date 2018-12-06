//
//  tool.hpp
//  CNLayerSimulation
//

#ifndef tool_hpp
#define tool_hpp

#include <stdio.h>

#include "cnformat.h"

// Tools class
class Tools {
private:
    // Data:
    
    // Function:
public:
    // Data:
    // Function:
    static string hexToBin(string hex);
    static string binToHex(string bin);
    static string strToHex(string str);
    static string hexToStr(string hex);
};

Tools tools;

#endif /* tool_hpp */
