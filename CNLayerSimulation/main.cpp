//
//  main.cpp
//  NetworkLayerSimulation
//
//  Created by Max on 2018/12/5.
//  Copyright © 2018 Max. All rights reserved.
//

#include <iostream>

#include "cnformat.h"
#include "interface.cpp"

int main(int argc, const char * argv[]) {
    ProcessIP IP;
    basisInformation.desIP[0] = "192";
    basisInformation.desIP[1] = "1";
    basisInformation.desIP[2] = "1";
    basisInformation.desIP[3] = "168";
    
    basisInformation.srcIP[0] = "192";
    basisInformation.srcIP[1] = "1";
    basisInformation.srcIP[2] = "1";
    basisInformation.srcIP[3] = "168";
    
    basisInformation.TTL = 255;
    Data ip;
    ip = IP.encapsulate("haha");
    cout << "head: " << ip.head;
    cout << endl;
    vector<DataFormat> ans = IP.interpret(ip);
    for (int i = 0; i < ans.size(); i++) {
        cout << ans[i].indexOfField << " " << ans[i].valueOfField << " " << ans[i].explainOfField << endl;
    }
    return 0;
}

