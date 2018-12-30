//
//  tool.hpp
//  CNLayerSimulation
//

#ifndef tool_hpp
#define tool_hpp

#include <stdio.h>
#include <fcntl.h>

#include "cnformat.h"
#include "apue.h"
#include "myerror.h"


using namespace std;

namespace Tools {
    static string hexToBin(string hex);
    static string binToHex(string bin);
    static string strToHex(string str);
    static string hexToStr(string hex);
    static string transfer(int x, int length);
    static string bmoc_calculation(string a, string b);
    int readFile(char* path, char* buff, int start, int length);
}

#endif /* tool_hpp */
