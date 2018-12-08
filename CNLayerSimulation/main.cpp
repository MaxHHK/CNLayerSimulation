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
    basisInformation.desPort = 12345;
    basisInformation.srcPort = 12345;
    basisInformation.srcIP[0] = "172";
    basisInformation.srcIP[1] = "0";
    basisInformation.srcIP[2] = "0";
    basisInformation.srcIP[3] = "1";
    basisInformation.desIP[0] = "172";
    basisInformation.desIP[1] = "0";
    basisInformation.desIP[2] = "0";
    basisInformation.desIP[3] = "1";
    
    ApplicationLayer sendEmail;
    string email = sendEmail.sendEmail();
    string dataFromApplication = strToHex(email);
    
    LayerInterpret tcp(TCP);
    tcp.interpret(email);
    
    LayerInterpret ip(IP);
    ip.interpret(tcp.encapsulatedData.head + tcp.encapsulatedData.dataOfUpLayer);
    
    email.clear();
    email = hexToStr(dataFromApplication);
    ApplicationLayer receiveEmail;
    sendEmail.writeEmail(email);
    
    return 0;
}

