//
//  _socket_.hpp
//  CNLayerSimulation
//

#ifndef _socket__hpp
#define _socket__hpp

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <errno.h>
#include <string>

#define MAX_LEN 255

enum SocketType {
    Server,
    Client
};

class SelfSocket {
public:
    SocketType typeOfSocket;
    int client_sock;
    int listen_sock;
    struct sockaddr_in server_addr;
    int hostnum;
    int buffSize;
    string run(string message="");
    SelfSocket(SocketType type, string desIP[], int desPort, int srcPort);
    ~SelfSocket();
private:
    void connectEmailServer();
    void bindSocket();
    void listenSocket(int listenLog);
    void acceptSocket();
    void sendMessageTo(std::string message);
    void loopSendAndRecviveMessage();
    string reveiveMessageFrom(bool showMsg=true);
    void closeSocket(int socketData);
};

#endif /* _socket__hpp */
