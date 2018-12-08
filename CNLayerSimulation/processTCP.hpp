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
private:
    string port_src;
    string port_des;
    string serial_number;
    string confirm_number;
    string data_offset;
    string keep;
    string urg;
    string ack;
    string psh;
    string rst;
    string syn;
    string fin;
    string window;
    string head_examination;
    string urgent_pointer;
    string option;
    string exam;
    
    string sourceIP;//伪首部需要
    string destinationIP;
public:
    // function
    Data encapsulate(const string fromUpLayer);
    Data disassemble(const string currentLayerData);
    vector <DataFormat> interpret(const Data);
};
#endif /* processTCP_hpp */
