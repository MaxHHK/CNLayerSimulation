//
//  TCPSource.cpp
//  CNLayerSimulation
//
//  Created by Max on 2018/12/30.
//  Copyright © 2018 Max. All rights reserved.
//

#include "TCPSource.hpp"


const string Source:: StateInfos[4] = {
    "SYN, ",
    "FIN, ",
    "PSH, ",
    "ACK"
};


bool Source:: mySleep(int ms) {
    clock_t tStart, tFinish;
    tStart = clock();
    ms *= 1000;
    for (; ; ) {
        tFinish = clock();
        if (tFinish > ms + tStart) {
            break;
        }
    }
    return true;
}

bool Source:: setFlags(int syn = 0, int fin = 0, int psh = 0, int ack = 1) {
    Flags[0] = syn == 0 ? 0 : 1;
    Flags[1] = fin == 0 ? 0 : 1;
    Flags[2] = psh == 0 ? 0 : 1;
    Flags[3] = ack == 0 ? 0 : 1;
    return true;
}

string Source:: makeTcp(int win, int len) {
    string sentence = "[";
    for (int i = 0; i < 4; i++) {
        if (Flags[i]) {
            sentence.append(StateInfos[i]);
        }
    }
    sentence.append("]");
    char suffix[100];
    sprintf(suffix, " Seq=%d Ack=%d Win=%d Len=%d", sequence, ack, win, len);
    sentence.append(suffix);
    return sentence;
}

bool Source:: dealTcp(string tcp) {
    sscanf(tcp.data(), "[SYN, ACK] Seq=%d Ack=%d Win=%d Len=%d", &sequence, &ack, &window, &length);
    
    cout << basisInformation.desPort << "-->" << basisInformation.srcPort << " " << tcp << endl;
    return true;
}

bool Source:: sendMsg(string msg) {
    cout << basisInformation.srcPort << "-->" << basisInformation.desPort << " " << msg << endl;
    mySleep(400);
    SelfSocket socket(Client, basisInformation.desIP, basisInformation.desPort, basisInformation.srcPort);
    socket.run(msg);
    return true;
}

string Source:: recvMsg(void) {
    mySleep(200);
    SelfSocket socket(Server, basisInformation.desIP, basisInformation.desPort, basisInformation.srcPort);
    string buf;
    buf = socket.run();
    return buf;
}


bool Source:: sendFile(string filePath) {
    int fileSize;
    int fd = open(filePath.data(), O_RDONLY, FILE_MODE);
    fileSize = static_cast<int>(lseek(fd, 0, SEEK_END));
    printf("%d\n", fileSize);
    return true;
}

bool Source:: startSend(string filePath) {
    
    if (connect()) {
        sendFile(filePath);
    }
    sleep(2);
    disconnect();
    printf("CLOSED");
    if (sequence == fileLength) {
        
    }
    return true;
}

bool Source:: connect() {
    setFlags(1);
    string first = makeTcp(14865, 0);
    sendMsg(first);
    
    string second = recvMsg();
    dealTcp(second);

    setFlags();
    string third = makeTcp(32455, 0);
    sendMsg(third);
    return true;
}

bool Source:: disconnect() {
    setFlags(0, 1);
    string first = makeTcp(52288, 0);
    sendMsg(first);
    
    string second = recvMsg();
    
    setFlags();
    string forth = makeTcp(52288, 0);
    sendMsg(forth);
    return true;
}

Source:: Source() {
    sequence = 1000;
    ack = 1000;
    fileOffset = 0;
}
