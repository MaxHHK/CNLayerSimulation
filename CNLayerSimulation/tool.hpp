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
    string readFile(const char* path, char* buff, int start, int length);
    static string base64_encode(unsigned char const* bytes_to_encode, unsigned int in_len);
    static string base64_decode(string const& encoded_string);
}

#endif /* tool_hpp */
