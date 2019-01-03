//
//  TCPSource.cpp
//  CNLayerSimulation
//
//  Created by Max on 2018/12/30.
//  Copyright � 2018 Max. All rights reserved.
//

#include "TCPSource.hpp"


const string Source:: StateInfos[4] = {
    "SYN, ",
    "FIN, ",
    "PSH, ",
    "ACK"
};

const string Source:: TCPAutoInfos[11] = {
    "CLOSED", "LISTEN", "SYN_RCVD", "SYN_SENT", "ESTABLISHED", "FIN_WAIT_1", "FIN_WAIT_2", "CLOSING", "TIME_WAIT", "CLOSE_WAIT", "LAST_ACK"
};

const string Source:: AlgoTypes[4] = {
    "using slow start",
    "using escaping",
    "get ack x 3, using fast retransmit",
    "timer out of time, retransmit"
};


bool Source:: mySleep(int ms) {
    if (debug) {
        return true;
    }
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
    char suffix[2048];
    sprintf(suffix, " Seq=%d Ack=%d Win=%d Len=%d", sequence, ack, win, len);
    sentence.append(suffix);
    return sentence;
}

bool Source:: dealTcp(string tcp) {
    vector<string> acks = printAllTCPs(tcp, true, true);
    for (vector<string>::iterator it = acks.begin(); it < acks.end(); it++) {
        dealSingleAck(*it);
    }
    return true;
}

int Source:: dealSingleAck(string singleAck) {
    setFlags();
    for (int i = 0; i < singleAck.length(); i++) {
        switch (singleAck[i]) {
            case ']':
                singleAck = singleAck.substr(i+2, singleAck.length() - i);
                break;
            case 'S':
                Flags[0] = 1;
                i += 2;
            case 'F':
                Flags[1] = 1;
                i += 2;
            case 'P':
                Flags[2] = 1;
                i += 2;
            case 'A':
                Flags[3] = 1;
                i += 2;
            default:
                break;
        }
    }
    sscanf(singleAck.data(), "Seq=%d Ack=%d Win=%d Len=%d", &ack, &yourAck, &window, &length);
    ack++;
    ack += length;
//    ssthresh = window / MSS;
    return true;
}

bool Source:: sendMsg(string msg) {
    printAllTCPs(msg, false, true);
    if (debug) {
        return true;
    } else {
        
        //printf("80 --> %d %s\n", basisInformation.desPort, msg.data());
        //inter.printAtSegment(inter.edge, lines++, "80 --> %d %s\n", basisInformation.desPort, msg.data());
    }
    fflush(stdout);
    
    mySleep(timeInter * 2);
    SelfSocket socket(Client, basisInformation.desIP, desPort, srcPort);
    socket.run(msg);
    socket.~SelfSocket();
    desPort++;
    srcPort++;
    return true;
}

string Source:: recvMsg(void) {
    
    if (debug) {
        return "";
    }
    
    mySleep(timeInter);
    SelfSocket socket(Server, basisInformation.desIP, desPort, srcPort);
    string msg;
    msg = socket.run();
    socket.~SelfSocket();
    desPort++;
    srcPort++;
    return msg;
}

bool Source:: sendFile() {
    fd = open(filePath.data(), O_RDONLY, FILE_MODE);
    fileSize = static_cast<int>(lseek(fd, 0, SEEK_END));
    useAlgorithmSendTCP();
    return true;
}

string Source:: encapsulateData() {
    string trueMsg = "";
    char  data[MSS + 1024];
    int i;
    for (i = 0; i < cwnd && fileOffset < fileSize; i++) {
        int localsize = fileOffset + MSS > fileSize ? fileSize - fileOffset : MSS;
        if (debug) {
            debugFile << "offset:" << fileOffset << "sieze:" << fileSize << endl;
        }
        setFlags();
        trueMsg.append(makeTcp(window, localsize) + "$$");

        readFile(filePath.data(), data, fileOffset, localsize);
        debugFile << endl << strlen(data) << endl;
        string result = Tools::base64_decode(data);

        write(dupFile, result.data(), result.size());
        
        data[strlen(data)] = 0;
        trueMsg.append(data);
        trueMsg.append("$$");
        
        fileOffset += (localsize);
        sequence += (localsize);
    }
    sendCwnd = i;
    return trueMsg;
}

bool Source:: useAlgorithmSendTCP() {
    string tcp, trueMsg;
    int algo = 0;
    cwnd = 1;
    strOfWindows = "01$$";
    while (fileOffset < fileSize) {
        printSegment(AlgoTypes[algo]);
        trueMsg.clear();
        lastOffSet = fileOffset;
        trueMsg = strOfWindows + encapsulateData();
        
        if (cwnd >= 10) {
            trueMsg[0] = sendCwnd / 10 + '0';
            trueMsg[1] = sendCwnd % 10 + '0';
        } else {
            trueMsg[0] = '0';
            trueMsg[1] = sendCwnd + '0';
        }
        
        lastSendMsg = trueMsg;
        sendMsg(trueMsg);
        debugFile << "\n\n---"<< trueMsg.size() << endl << "left: " << fileOffset << " Send:" << trueMsg << endl;
        
        string allacks = recvMsg();
        
        debugFile << "\n\n---Recv:" << allacks << endl;
        
        if (debug) {
            allacks = "00$$[111$$[222$$[333$$";
        }
        algo = dealAllAcks(allacks);
    }
    return true;
}

int Source:: slowStart(string allAcks) {
    dealTcp(allAcks);
    if (ssthresh > cwnd && !isCongest) {
        cwnd *= 2;
        return 0;
    } else {
        if (cwnd < realMax) {
            cwnd++;
        }
        return 1;
    }
    return 0;
}

bool Source:: fastRetransimit(string allAcks, int numOfLast) {
    dealTcp(allAcks);
    isCongest = true;
    vector<string> acks = printAllTCPs(lastSendMsg, true, false);
    
    printSegment(AlgoTypes[2]);
    
    sendMsg("01$$" + acks[numOfLast*2] + "$$" + acks[numOfLast*2+1] + "$$");
    string ackFast = recvMsg();
    dealAllAcks(ackFast);
    if (ssthresh >= 4) {
        ssthresh = cwnd / 2;
        cwnd = ssthresh;
    }
    return true;
}

bool Source:: outOfTime() {
    cwnd = 1;
    ssthresh = cwnd / 2;
    fileOffset = lastOffSet;
    return true;
}

int Source:: dealAllAcks(string allAcks) {
    switch (allAcks[0]) {
        case '0':
            return slowStart(allAcks);
        case '1':
            outOfTime();
            printSegment(AlgoTypes[3]);
            return 1;
        case '2':
            fastRetransimit(allAcks, allAcks[1] - '0');
            return 2;
        default:
            break;
    }
    return 5;
}

vector<string> Source:: printAllTCPs(string allacks, bool isAcks = true, bool isPrint = false) {
    vector<string> tcps;
    printInfos.clear();
    char buf[2048], portInfos[2048];
    if (isAcks) {
        sprintf(portInfos, "%d --> 80", basisInformation.srcPort);
    } else {
        sprintf(portInfos, "80 --> %d", basisInformation.desPort);
    }
    if (allacks[2] != '$') {
        tcps.push_back(allacks);
        sprintf(buf, "%s %s", portInfos, tcps[0].data());
        printInfos.push_back(buf);
    } else {
        int next = 4, cutend = 40;
        for (int i = 4; i < allacks.length(); i++) {
            for (int j = i; j < allacks.length(); j++) {
                if (allacks[j] == '$') {
                    allacks[j] = 0;
                    next = j + 1;
                    break;
                }
            }
            if (allacks[i] == '[') {
                tcps.push_back(allacks.substr(i, next - i));
            } else {
                if (allacks.length() - i < 40) {
                    cutend = static_cast<int>(allacks.length() - i - 1);
                }
                string subMsg = allacks.substr(i, cutend) + "...";
                for (int j = 0; j < subMsg.size(); j++) {
                    if (subMsg[j] == 10) {
                        subMsg[j] = '\\';
                        subMsg.insert(j+1, 1, 'n');
                    }
                }
                tcps.push_back(subMsg);
            }
            i = next;
        }
        for (int i = 0; i < tcps.size(); i++) {
            sprintf(buf, "%s %s", portInfos, tcps[i].data());
            if (!isAcks) {
                strcat(buf, ("[data="+tcps[i+1]+"]").data());
                i++;
            }
            printInfos.push_back(buf);
        }
    }
    if (isPrint) {
        printSegment("");
    }
    return tcps;
}

bool Source:: printSegment(string msg, bool isState) {
    putchar('|');
    for (int i = 0; i < 149; i++) {
        putchar('-');
    }
    printf("|\n");
    if (msg == "") {
        for (vector<string>::iterator it = printInfos.begin(); it < printInfos.end(); it++) {
            printf("|[%2d] %-144s|\n", lines++, it->data());
        }
    } else {
        if (isState) {
            putchar('|');
            for (int i = 0; i < 149; i++) {
                putchar('*');
            }
            printf("|\n");
            printf("\033[%dm",(34));
            printf("|%-49s%-100s|\n", " ", ("TCP State: "+msg).data());
            putchar('|');
            printf("\033[%dm",(37));
            for (int i = 0; i < 149; i++) {
                putchar('*');
            }
            printf("|\n");
        } else {
            printf("\033[%dm",(31));
            printf("|%49s%-100s|\n", " ", ("(Infor: "+msg+")").data());
            printf("\033[%dm",(37));
        }
    }
    return true;
}

bool Source:: startSend(string filePath) {
    system("clear");
    this->filePath = filePath;
    if (debug) {
        sendFile();
        return "";
    }
    printSegment(TCPAutoInfos[CLOSED], true);
    if (connect()) {
        mySleep(timeInter * 3);
        printSegment(TCPAutoInfos[ESTABLISHED], true);
        sendFile();
        debugFile << "end sending";
        mySleep(timeInter * 2);
    }
    disconnect();
    printSegment(TCPAutoInfos[CLOSED], true);
    return true;
}

bool Source:: connect() {
    printSegment(TCPAutoInfos[SYN_SENT], true);
    setFlags(1);
    char first[1024];
    sprintf(first, "[SYN] Seq=%d Win=%d Len=%d MSS=%d", sequence, 32455, 0, MSS);
    sendMsg(first);
    sequence++;
    
    string second = recvMsg();
    dealTcp(second);
    
    setFlags();
    string third = makeTcp(32455, 0);
    sendMsg(third);
    return true;
}

bool Source:: disconnect() {
    setFlags(0, 1);
    printSegment(TCPAutoInfos[FIN_WAIT_1], true);
    string first = makeTcp(52288, 0);
    debugFile << first;
    sendMsg(first);
    sequence++;
    
    string second = recvMsg();
    printSegment(TCPAutoInfos[FIN_WAIT_2], true);
    dealTcp(second);
    
    string third = recvMsg();
    dealTcp(third);
    
    setFlags();
    string forth = makeTcp(52288, 0);
    sendMsg(forth);
    return true;
}

Source:: Source() {
    debugFile.open("DebugLog", ios::in|ios::out);
    lines = 1;
    sequence = rand() % 1000 + 2000;
    ack = 1000;
    fileOffset = 0;
    MSS = 100;
    
    ssthresh = 4;
    timeInter = 200;
    debug = false;
    srcPort = basisInformation.srcPort;
    desPort = basisInformation.desPort;
    printInfos.clear();
    isCongest = false;
    realMax = 6;
    dupFile = open("testdup", O_RDWR | O_CREAT | O_TRUNC, FILE_MODE);
}
