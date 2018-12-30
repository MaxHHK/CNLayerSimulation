//
//  main.cpp
//  NetworkLayerSimulation
//
//  Created by Max on 2018/12/5.
//  Copyright © 2018 Max. All rights reserved.
//

#include <iostream>

#include "cnformat.h"
#include "TCPSource.cpp"

int main(int argc, const char * argv[]) {
    //Shell shell;
    //shell.startShell();
    
    
    basisInformation.desPort = 12346;
    basisInformation.srcPort = 12346;
    basisInformation.srcIP[0] = "172";
    basisInformation.srcIP[1] = "20";
    basisInformation.srcIP[2] = "10";
    basisInformation.srcIP[3] = "7";
    basisInformation.desIP[0] = "172";
    basisInformation.desIP[1] = "20";
    basisInformation.desIP[2] = "10";
    basisInformation.desIP[3] = "2";
    
    Source source;
    source.startSend("file");
    
    return 0;
}

