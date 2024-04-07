#include "udp_client.h"

namespace COMMON{

UDPClient::UDPClient(const char* serverIP, int port, UDPClient_CALLBACK_FUN call_back) 
: WorkBase(COMMON::TIME)
{
    pCallBack_ = call_back;
    sockfd = -1;
    ConnectServer();
    memset(&serverAddr, 0, sizeof(serverAddr));
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(port);
    inet_pton(AF_INET, serverIP, &serverAddr.sin_addr);
}

UDPClient::~UDPClient() 
{
    close(sockfd);
}


bool UDPClient::ConnectServer()
{
    sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    if (sockfd < 0) 
    {
        std::cerr << "Error creating socket" << std::endl;
        return false;
    }
    return true;
}

void UDPClient::WorkFun()
{
    char buffer[1024];
    memset(buffer, 0, sizeof(buffer));
    size_t len = recvfrom(sockfd, buffer, sizeof(buffer), 0, nullptr, nullptr);
    std::string data(buffer, len);
    pCallBack_(data);
}

}



