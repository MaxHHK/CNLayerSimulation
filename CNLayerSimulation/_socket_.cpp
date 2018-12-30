//
//  _socket_.cpp
//  CNLayerSimulation
//

#include "_socket_.hpp"
#include <iostream>
#include <ctime>

SelfSocket::SelfSocket(SocketType type, string desIP[], int desPort, int srcPort){
    int i;
    string ipaddr = "";
    for(i = 0; i < 4; ++i) {
        ipaddr += desIP[i] +'.';
    }
    ipaddr.pop_back();
    buffSize = 255;
    typeOfSocket = type;
    if (typeOfSocket == Client) {
        const char* ipAddress = ipaddr.data();
        server_addr.sin_family = AF_INET;
        server_addr.sin_port = htons(desPort);
        inet_aton(ipAddress, &server_addr.sin_addr);
        memset(&server_addr.sin_zero, 0, sizeof(server_addr.sin_zero));
        if ((client_sock = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
            perror("create socket failed");
            exit(0);
        }
    } else if (typeOfSocket == Server) {
        server_addr.sin_family = AF_INET;
        server_addr.sin_port = htons(srcPort);
        server_addr.sin_addr.s_addr = htonl(INADDR_ANY);
        memset(&server_addr.sin_zero, 0, sizeof(server_addr.sin_zero));
        if((listen_sock = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
            perror("create socket failed");
            exit(0);
        }
    }
}


SelfSocket::~SelfSocket() {
    if(typeOfSocket == Server) {
        close(client_sock);
        close(listen_sock);
    } else if (typeOfSocket == Client) {
        close(client_sock);
    }
    
}

void SelfSocket::connectEmailServer() {
    if (connect(client_sock, (struct sockaddr *)&server_addr, sizeof(server_addr)) == -1) {
        perror("connect failed\n");
        exit(0);
    }
}

void SelfSocket::bindSocket() {
    if (bind(listen_sock, (struct sockaddr *)&server_addr, sizeof(server_addr)) == -1) {
        perror("bind failed\n");
        exit(0);
    }
}

void SelfSocket::loopSendAndRecviveMessage() {
    string sendMessage;
    while(1) {
        cin >> sendMessage;
        const char* sendMsg = sendMessage.data();
        if(send(client_sock, sendMsg, strlen(sendMsg) + 1, 0) == -1) {
            perror("send failed\n");
        }
        char* receiveMsg = NULL;
        if (recv(client_sock, receiveMsg, buffSize, 0) == -1){
            perror("recv failed\n");
        }
        sendMessage.clear();
    }
}

void SelfSocket::sendMessageTo(string message) {
    const char *sendMessage = message.data();
    if(send(client_sock, sendMessage, strlen(sendMessage) + 1, 0) == -1) {
        perror("send failed\n");
    }
}

string SelfSocket::reveiveMessageFrom(bool showMsg) {
    char receiveMessage[buffSize];
    memset(receiveMessage, 0, buffSize);
    if (recv(client_sock, receiveMessage, buffSize, 0) == -1){
        perror("recv failed\n");
    }
    if(showMsg) {
        cout << receiveMessage << endl;
    }
    string receiveMsg = receiveMessage;
    return receiveMsg;
}

void SelfSocket::listenSocket(int listenLog) {
    if (listen(listen_sock, listenLog) == -1) {
        perror("listen failed\n");
        exit(0);
    }
}

void SelfSocket::acceptSocket() {
    if ((client_sock = accept(listen_sock, NULL, NULL)) == 0) {
        perror("accept failed");
    }
}

void SelfSocket::closeSocket(int socketData) {
    if (close(socketData) == -1) {
        perror("close failed\n");
        exit(0);
    }
}

string SelfSocket::run(string hexMessage) {
    string result = "";
    if(typeOfSocket == Client) {
        connectEmailServer();
        sendMessageTo(hexMessage);
    } else if(typeOfSocket == Server) {
        bindSocket();
        listenSocket(1);
        acceptSocket();
        // server.sendMessageTo(test);
        result = reveiveMessageFrom(false);
    }
    return result;
}
