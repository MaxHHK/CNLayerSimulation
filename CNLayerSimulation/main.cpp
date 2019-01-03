//
//  main.cpp
//  NetworkLayerSimulation
//
//  Created by Max on 2018/12/5.
//  Copyright © 2018 Max. All rights reserved.
//

#include <iostream>

#include "cnformat.h"
#include "Shell.cpp"

int main(int argc, const char * argv[]) {
    if (argc > 2) {
        // local test
        basisInformation.desPort = 12349;
        basisInformation.srcPort = 12349;
        basisInformation.srcIP[0] = "127";
        basisInformation.srcIP[1] = "0";
        basisInformation.srcIP[2] = "0";
        basisInformation.srcIP[3] = "1";

        basisInformation.desIP[0] = "127";
        basisInformation.desIP[1] = "0";
        basisInformation.desIP[2] = "0";
        basisInformation.desIP[3] = "1";
    } else {
        // test between two mac
        basisInformation.desPort = 12349;
        basisInformation.srcPort = 12349;
        basisInformation.srcIP[0] = "172";
        basisInformation.srcIP[1] = "20";
        basisInformation.srcIP[2] = "10";
        basisInformation.srcIP[3] = "7";
        
        basisInformation.desIP[0] = "172";
        basisInformation.desIP[1] = "20";
        basisInformation.desIP[2] = "10";
        basisInformation.desIP[3] = "2";
    }

    Shell shell;
    shell.startShell();
    
    return 0;
}

