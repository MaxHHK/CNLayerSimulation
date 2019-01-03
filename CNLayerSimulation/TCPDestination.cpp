//
//  TCPDestination.cpp
//  CNLayerSimulation
//
//  Created by Max on 2018/12/30.
//  Copyright © 2018 Max. All rights reserved.
//

#include "TCPDestination.hpp"
#include <random>
// #include "base64.cpp"
#define BUFFSIZE 2048
#define LINEMAX 120
#define random(x) (rand()%x)
#define left(x) printf("\033[%dC", x);
#define right(x) printf("\033[%dD", x);
#ifdef _tool_
#include "tool.cpp"
#endif

int getRand(int max) {
    srand((int)clock());
    return random(max);
}

Destination::Destination() {
    Sequence = getRand(3000);
    Acknowage = 0;
    while ((Window = getRand(3000)) < 1000);
    sourceSeq = 0;
    sourceAck = 0;
    sourceLen = 0;
    sourceWin = 0;
    totalPacks = 0;
    portadd = 0;
    Len = 0;
    memset(seqs, 0, 20);
    memset(acks, 0, 20);
    memset(lens, 0, 20);
    memset(wins, 0, 20);
}


void Destination:: printStats(TCPAutomation statFlag) {
    string statment;
    switch (statFlag) {
        case CLOSED: statment = "CLOSED"; break;
        case LISTEN: statment = "LISTEN"; break;
        case SYN_RCVD: statment = "SYN_RCVD"; break;
        case ESTABLISHED: statment = "ESTABLISHED"; break;
        case CLOSE_WAIT: statment = "CLOSE_WAIT"; break;
        case LAST_ACK: statment = "LAST_ACK"; break;
        default: break;
    }
    for(int i = 0; i < LINEMAX + 5; ++i) {
        putchar('+');
    }
    putchar('\n');
    for(int i = 0; i < LINEMAX/2; ++i) {
        putchar('+');
    }
    cout << statment;
    for(int i = 0; i < LINEMAX/2 + 5 - statment.length(); ++i) {
        putchar('+');
    }
    putchar('\n');
    for(int i = 0; i < LINEMAX + 5; ++i) {
        putchar('+');
    }
    putchar('\n');
}

bool Destination::mySleep(int ms) {
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

void Destination::printFunction(const char* msg, FromOrTo flag, bool retrans=false, char* data=NULL) {
    totalPacks += 1;
    printf("++ ");
    left(20);
    printf(" [%d]", totalPacks);
    if(retrans) {
        printf(" (retransmission)");
    }
    if (flag == Fromsrc) { //from
        printf(" %d --> %d %s", basisInformation.srcPort, 80, msg);
        
    } else {
        printf(" %d --> %d %s",  80, basisInformation.desPort, msg);
    }
    if(data) {
        
        printf("  [");
        int max = strlen(data) > 10 ? 10 :  static_cast<int>( strlen(data) );
        for(int i = 0; i < max; ++i) {
            putchar(*(data + i));
        }
        printf("...]");
    }
    right(LINEMAX);
    left(LINEMAX + 5 - 2);
    printf("++\n");
}

string Destination::startReceive(const char* saveFilePath) {
    system("clear");
    // file2 = fopen(saveFilePath, "w");
    int fd = open(saveFilePath, O_RDWR | O_CREAT | O_TRUNC, FILE_MODE);
    
    string fileSeq(saveFilePath);
    //    cout << "receive" << endl;
    
    if(establishTcpConnection()) {
        mySleep(200);
        recvDatas(fd);
        mySleep(200);
    }
    putchar('\n');
    
    string test("cat ");
    test += fileSeq;
    
    //    system(test.data());
    
    putchar('\n');
    
    return string(saveFilePath);
}



//接受数据
bool Destination::recvDatas(int fd) {
    char *temp;
    while(1) {
        string recvMsg = recvmsg();
        temp = (char*) (recvMsg.data());
        if (recvMsg[0] != '[') {
            int packNums;
            int mark = 0;
            int lossPackNum = -1;
            int lossFlag=0;
            // char writeBuff[65535];
            string sendMsg;
            // memset(writeBuff, 0, 65535);
            mark = getNext(mark, temp);
            packNums = atoi(recvMsg.data());
            // cout << recvMsg.length() << endl;
            // cout << "package:" << packNums << endl;
            // cout << recvMsg << endl;
            // putchar('\n');
            for(int i = 0; i < packNums; ++i) {
                if(mark >= recvMsg.length()) {
                    packNums = i;
                    break;
                }
                int tcpMsg = mark;
                mark = getNext(mark, temp);
                //随机概率超时
                if (i == 0 && getRand(100) > 95) {
                    lossFlag = timeout;
                    break;
                }
                int writeOffset = mark;
                //固定丢包
                if (packNums >= 5 &&  i == packNums - 2 ) {
                    lossPackNum = i;
                    lossFlag = losspack;
                    sendMsg += "2" + to_string(i) + "$$";
                } else {
                    printFunction(temp + tcpMsg, Fromsrc, false);
                }
                sscanf(temp + tcpMsg, "[ACK] Seq=%d Ack=%d Win=%d Len=%d", &sourceSeq, &sourceAck, &sourceWin, &sourceLen);
                seqs[i] = sourceSeq;
                acks[i] = sourceAck;
                lens[i] = sourceLen;
                wins[i] = sourceWin;
                mark = getNext(mark, temp);
                // printf("%d\n", strlen(temp + writeOffset));
                // printf("%s\n", temp + writeOffset);
                string undecode(temp + writeOffset);
                
                string res = Tools::base64_decode(undecode);
                // strcat(writeBuff, res.data());
                // cout << res.length() << endl;
                write(fd, res.data(), res.length());
                // cout << res.data() << endl;
            }
            //超时
            if (lossFlag == timeout) {
                cout << "++";
                left(20);
                cout << "  (timeout)";
                right(LINEMAX);
                left(LINEMAX + 5 - 2);
                printf("++\n");
                sendmsg("10$$");
                continue;
            } else if (lossFlag == normal) {//没有异常
                sendMsg = "00$$";
            }
            
            
            
            //写文件
            
            // printf("writeBuff:\n%s\n", writeBuff);
            // write(fd, writeBuff, strlen(writeBuff));
            // fwrite(writeBuff, sizeof(char), strlen(writeBuff), file2);
            for(int i = 0; i < packNums; ++i) {
                char sendBuff[BUFFSIZE];
                int j = i;
                if(lossFlag == losspack && i >= lossPackNum) {
                    j = lossPackNum - 1;
                }
                Acknowage = seqs[j] + lens[j];
                sprintf(sendBuff, "[ACK] Seq=%d Ack=%d Win=%d Len=%d", Sequence, Acknowage, Window, 0);
                string temp((const char*)sendBuff);
                printFunction(sendBuff, Tosrc);
                sendMsg = sendMsg + temp + "$$";
            }
            // cout << sendMsg.data() << endl;
            sendmsg(sendMsg.data());
            if(lossFlag == losspack) {
                lossPackProc(packNums, lossPackNum);
            }
        } else { // 传输结束
            break;
        }
        
    }
    // cout << "recv ok!" << endl;
    releaseTcpConnection(temp);
    return 1;
}

//处理重传
void Destination:: lossPackProc(int packNums, int lossPackNum) {
    // cout << "retransmission" << endl;
    string retransimissionPack = recvmsg();
    // cout << "(retransmission) ";
    char* temp = (char*)(retransimissionPack.data());
    int mark = 0;
    mark = getNext(mark, temp);
    int tcpMsg = mark;
    getNext(mark, temp);
    printFunction(temp + tcpMsg, Fromsrc, true);
    
    Acknowage = seqs[packNums - 1] + lens[packNums - 1];
    char sendBuff[BUFFSIZE];
    memset(sendBuff, 0, BUFFSIZE);
    string sendMsg = "00$$";
    sprintf(sendBuff, "[ACK] Seq=%d Ack=%d Win=%d Len=%d", Sequence, Acknowage, Window, Len);
    string sendTemp((const char*)sendBuff);
    // cout << "(retransmission) ";
    printFunction(sendBuff, Tosrc, true);
    sendMsg = sendMsg + sendTemp + "$$";
    sendmsg(sendMsg.data());
}




// get next $$
int Destination::getNext(int mark, char* recvMsg) {
    for(; recvMsg[mark] != '$' && recvMsg[mark]; ++mark);
    recvMsg[mark] = 0;
    recvMsg[mark + 1] = 0;
    mark += 2;
    // printf("%s\n", recvMsg + mark);
    return mark;
}




bool  Destination::establishTcpConnection() {
    
    string first = recvmsg();
    for(int i = 0; i < LINEMAX + 5; ++i) {
        putchar('*');
    }
    putchar('\n');
    printStats(LISTEN);
    sscanf(first.data(), "[SYN] Seq=%d Win=%d Len=%d MSS=%d", &sourceSeq, &sourceWin, &sourceLen, &mss);
    char sendMsg[BUFFSIZE];
    printFunction(first.data(), Fromsrc);
    
    
    Acknowage = sourceSeq + 1;
    sprintf(sendMsg, "[SYN, ACK] Seq=%d Ack=%d Win=%d Len=%d MSS=%d", Sequence, Acknowage, Window, Len, mss);
    sendmsg(sendMsg);
    printFunction(sendMsg, Tosrc);
    printStats(SYN_RCVD);
    Sequence ++;
    string second = recvmsg();
    printFunction(second.data(), Fromsrc);
    
    printStats(ESTABLISHED);
    return 1;
}

bool Destination::releaseTcpConnection(const char* temp) {
    string recvFin1(temp);
    sscanf(recvFin1.data(), "[FIN, ACK] Seq=%d Ack=%d Win=%d Len=%d", &sourceSeq, &sourceAck, &sourceWin, &sourceLen);
    printFunction(recvFin1.data(), Fromsrc);
    
    printStats(CLOSE_WAIT);
    
    //send ack
    char sendAck[BUFFSIZE];
    memset(sendAck, 0, BUFFSIZE);
    Acknowage = sourceSeq + 1;
    sprintf(sendAck, "[ACK] Seq=%d Ack=%d Win=%d Len=%d", Sequence, Acknowage, Window, Len);
    sendmsg(sendAck);
    printFunction(sendAck, Tosrc);
    
    mySleep(500);
    //send fin 2
    char sendFin2[BUFFSIZE];
    memset(sendFin2, 0, BUFFSIZE);
    sprintf(sendFin2, "[FIN, ACK] Seq=%d Ack=%d Win=%d Len=%d", Sequence, Acknowage, Window, Len);
    sendmsg(sendFin2);
    printFunction(sendFin2, Tosrc);
    
    printStats(LAST_ACK);
    
    string last = recvmsg();
    sscanf(last.data(), "[ACK] Seq=%d Ack=%d Win=%d Len=%d", &sourceSeq, &sourceAck, &sourceWin, &sourceLen);
    printFunction(last.data(), Fromsrc);
    printStats(CLOSED);
    return true;
}







void initial() {
    system("clear");
    //    basisInformation.desPort = 12349;
    //    basisInformation.srcPort = 12349;
    //    basisInformation.srcIP[0] = "172";
    //    basisInformation.srcIP[1] = "20";
    //    basisInformation.srcIP[2] = "10";
    //    basisInformation.srcIP[3] = "7";
    //    basisInformation.desIP[0] = "172";
    //    basisInformation.desIP[1] = "20";
    //    basisInformation.desIP[2] = "10";
    //    basisInformation.desIP[3] = "2";
}
void Destination::sendmsg(const char* msg) {
    
    mySleep(400);
    SelfSocket SendSocket(Client, basisInformation.srcIP, basisInformation.srcPort + portadd, basisInformation.desPort + portadd);
    string s(msg);
    SendSocket.run(msg);
    SendSocket.~SelfSocket();
    portadd += 1;
    
}

string Destination::recvmsg() {
    mySleep(200);
    SelfSocket RecvSocket(Server, basisInformation.srcIP, basisInformation.srcPort + portadd, basisInformation.desPort + portadd);
    string recvMsg = RecvSocket.run();
    RecvSocket.~SelfSocket();
    portadd += 1;
    return recvMsg;
}
