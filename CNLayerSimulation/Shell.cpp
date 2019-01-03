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
    for (int i = 0; i < 6; i++) {
        basisInformation.srcMac[i].push_back('0' + rand() % 10);
        basisInformation.desMac[i].push_back('0' + rand() % 10);
        basisInformation.srcMac[i].push_back('0' + rand() % 10);
        basisInformation.desMac[i].push_back('0' + rand() % 10);
    }
    inter.moveToCommand();
    cout << "automate? ";
    cin >> interval;
    getchar();
    return true;
}

bool Shell:: runServer(string msg = "") {
    string filePath, msgFromPhysics, email;
    fflush(stdout);
    
    Destination des;
    filePath = des.startReceive("file.png");
    fflush(stdout);
    
    SelfSocket server(type, basisInformation.desIP, basisInformation.desPort, basisInformation.srcPort);
    
    inter.printBoard(inter.edge);
    inter.moveToCommand();
    
    fflush(stdout);
    
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
    
    receiveEmail.writeEmail(hexToStr(tcp.encapsulatedData.dataOfUpLayer), filePath);
    
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
    
    
    Source source;
    source.startSend(emailClient.filePath);
    
    sleep(2);
    
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
