//
//  Shell.cpp
//  CNLayerSimulation
//
//  Created by Max on 2018/12/30.
//  Copyright © 2018 Max. All rights reserved.
//

#include "Shell.hpp"

// shell class

bool Shell:: welcomeWindow(void) {
    Window userWin(10, 60, 20, 4, false, "User");
    Window passWin(14, 60, 20, 4, false, "Password");
    Window typeWin(16, 60, 20, 4, false, "You are ?");
    
    inter.printBoard(userWin);
    inter.printBoard(passWin);
    inter.printBoard(typeWin);
    string username = inter.getLine(userWin);
    string password = inter.getLine(passWin, true);
    string typeString = inter.getLine(typeWin);
    
    if (typeString == "Server") {
        type = Server;
    } else {
        type = Client;
    }
    
    inter.printBoard(inter.edge);
    inter.printAtSegment(inter.edge, 10, 50, inter.FRONT_RED, "Log in successful!");
    
    return true;
}

bool Shell:: initialInfo(void) {
    basisInformation.desPort = 12345;
    basisInformation.srcPort = 12345;
    basisInformation.srcIP[0] = "172";
    basisInformation.srcIP[1] = "20";
    basisInformation.srcIP[2] = "10";
    basisInformation.srcIP[3] = "2";
    basisInformation.desIP[0] = "172";
    basisInformation.desIP[1] = "20";
    basisInformation.desIP[2] = "10";
    basisInformation.desIP[3] = "2";
    for (int i = 0; i < 6; i++) {
        basisInformation.srcMac[i].push_back('0' + rand() % 10);
        basisInformation.desMac[i].push_back('0' + rand() % 10);
        basisInformation.srcMac[i].push_back('0' + rand() % 10);
        basisInformation.desMac[i].push_back('0' + rand() % 10);
    }
    inter.moveToCommand();
    cout << "automate? ";
    cin >> interval;
    return true;
}

bool Shell:: runServer(string msg = "") {
    SelfSocket server(type, basisInformation.desIP, basisInformation.desPort, basisInformation.srcPort);
    string msgFromPhysics, email;
    
    inter.printBoard(inter.edge);
    inter.moveToCommand();
    
    fflush(stdout);
    
    
    // test
    
    //    LayerInterpret mac(Mac);
    //    mac.interpret(msg, 0, false);
    //
    //    LayerInterpret ip(IP);
    //    ip.interpret(mac.encapsulatedData.dataOfUpLayer, 0, false);
    //
    //    LayerInterpret tcp(TCP);
    //    tcp.interpret(ip.encapsulatedData.dataOfUpLayer, 0, false);
    
    // test
    
    
    msgFromPhysics = server.run();
    msg = hexToStr(msgFromPhysics);
    msg = msgFromPhysics;
    
    LayerInterpret mac(Mac);
    mac.interpret(msg, 0, false);
    
    LayerInterpret ip(IP);
    ip.interpret(mac.encapsulatedData.dataOfUpLayer, 0, false);
    
    LayerInterpret tcp(TCP);
    tcp.interpret(ip.encapsulatedData.dataOfUpLayer, 0, false);
    
    ApplicationLayer receiveEmail;
    cout << hexToStr(tcp.encapsulatedData.dataOfUpLayer);
    receiveEmail.writeEmail(hexToStr(tcp.encapsulatedData.dataOfUpLayer));
    
    return true;
}

bool Shell:: runClient(void) {
    SelfSocket client(type, basisInformation.desIP, basisInformation.desPort, basisInformation.srcPort);
    string cmd, email, dataFromApplication;
    
    cmd = inter.getLine(inter.edge);
    
    ApplicationLayer emailClient;
    email = emailClient.sendEmail();
    dataFromApplication = strToHex(email);
    
    LayerInterpret tcp(TCP);
    tcp.interpret(dataFromApplication, interval);
    
    LayerInterpret ip(IP);
    ip.interpret(tcp.encapsulatedData.head + tcp.encapsulatedData.dataOfUpLayer, interval);
    
    LayerInterpret mac(Mac);
    mac.interpret(ip.encapsulatedData.head + ip.encapsulatedData.dataOfUpLayer, interval);
    
    //test
    //runServer(mac.encapsulatedData.head + mac.encapsulatedData.dataOfUpLayer + mac.encapsulatedData.tail);
    
    client.run(mac.encapsulatedData.head + mac.encapsulatedData.dataOfUpLayer + mac.encapsulatedData.tail);
    
    return true;
}

bool Shell:: startShell() {
    
    if (type == Server) {
        return runServer();
    } else {
        return runClient();
    }
}
