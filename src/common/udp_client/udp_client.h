#ifndef UDP_CLIENT_H
#define UDP_CLIENT_H
#include <iostream>
#include <cstring>
#include <arpa/inet.h>
#include <unistd.h>
#include <functional>
#include "common/work_base/work_base.h"

namespace COMMON{


class UDPClient : public WorkBase
{

typedef std::function<void(std::string&)> UDPClient_CALLBACK_FUN;

public:
    UDPClient(const char* serverIP, int port, UDPClient_CALLBACK_FUN call_back);
    ~UDPClient();

    bool ConnectServer();
    void sendMessage(const char* message, int size) {
        sendto(sockfd, message, size, 0, (struct sockaddr*)&serverAddr, sizeof(serverAddr));
    }
    void WorkFun();
private:
    int sockfd;
    struct sockaddr_in serverAddr;
    UDPClient_CALLBACK_FUN pCallBack_;
};

}
#endif