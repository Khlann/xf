#include "tcp_client.h"
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/ioctl.h>
#include <fcntl.h>
#include <cstring>
#include <iostream>

namespace COMMON{
TcpClient::TcpClient()
{
    iSockfd_ = -1;
    bIsStop_ = false;
    iBuffSize_ = 1024;
    bISConnect_ = false;
}

TcpClient::TcpClient(std::string &server_ip, int port)
    : strServerIP_(server_ip)
    , iPort_(port)
{
    iSockfd_ = -1;
    bIsStop_ = false;
    iBuffSize_ = 1024;
    bISConnect_ = false;
    iSockfd_ = socket(AF_INET, SOCK_STREAM, 0);
    if(iSockfd_ < 0){
        std::cout << "socket error" << std::endl;
    }
}

TcpClient::~TcpClient()
{
    Stop();
    if (thComm_.joinable())
    {
        thComm_.join();
    }
    close(iSockfd_);
    iSockfd_ = -1;
    std::cout << "~TcpClient" <<std::endl;
}

void TcpClient::Stop()
{
    bIsStop_ = true;
    if (bISConnect_)
    {
        shutdown(iSockfd_, SHUT_RDWR);
    }
}


bool TcpClient::Start()
{
    if (ConnectServer())
    {
        thComm_ = std::thread(&TcpClient::CommThread, this);
        return true;
    }
    return false;
}


void TcpClient::SetServerIP(std::string &server_ip)
{
    strServerIP_ = server_ip;
}


void TcpClient::SetServerPort(int port)
{
    iPort_ = port;
}


bool TcpClient::SetBlockOpt(int m_fd,bool blocked)
{
//    qDebug() << "SetBlockOpt";
    int  flags;
    flags = fcntl(m_fd, F_GETFL, 0);
    if(flags < 0)
    {
        return false;
    }
    if(blocked)
    {
        flags &= ~O_NONBLOCK;
    }
    else
    {
        flags |= O_NONBLOCK;
    }
    if(fcntl(m_fd, F_SETFL, flags) < 0)
    {
        return false;
    }
    return true;
}

bool TcpClient::ConnectServer()
{
    if (bISConnect_)
    {
        return true;
    }
    if (iSockfd_ < 0)
    {
        iSockfd_ = socket(AF_INET, SOCK_STREAM, 0);
        if(iSockfd_ < 0){
            std::cout << "socket error" << std::endl;
            return false;
        }
    }

    struct sockaddr_in ser;
    ser.sin_family = AF_INET;
    ser.sin_port=htons(iPort_);
    ser.sin_addr.s_addr=inet_addr(strServerIP_.c_str());

    socklen_t len = sizeof(struct sockaddr_in);
    SetBlockOpt(iSockfd_, false);
    if(connect(iSockfd_, (struct sockaddr*)&ser, len) < 0)
    {
        return false;
    }
    bISConnect_ = true;
    SetBlockOpt(iSockfd_, true);
    return true;
}

bool TcpClient::CheckValidData(std::string &data, int &valid_start, int &valid_size)
{
    if (data.size() != 0)
    {
        valid_start = 0;
        valid_size = (int)data.size();
        return true;
    }
    valid_start = 0;
    valid_size = 0;
    return false;
}


void TcpClient::SetBuffSize(int size)
{
    iBuffSize_ = size;
}


bool TcpClient::IsConnectServer()
{
    return bISConnect_;
}


bool TcpClient::SendData(const char *data, int size)
{

    if (bISConnect_)
    {
        try
        {
            if (send(iSockfd_, data, size, 0) <= 0)
            {
                return false;
            }
            return true;
        }
        catch (std::exception& e)
        {
            std::cout << e.what() << std::endl;
            return false;
        }
    }
    return false;
}


void TcpClient::CommThread()
{
    char* temp_buff = new char[iBuffSize_];
    std::string buff_data;
    while (!bIsStop_)
    {
        std::memset(temp_buff, 0, iBuffSize_);
        int data_size = recv(iSockfd_, temp_buff, 1023, 0);
        if(data_size <= 0)
        {
            bISConnect_ = false;
//            qDebug()<< "recv error";
            if (bIsStop_)
            {
                iSockfd_ = -1;
                break;
            }
            if (!ConnectServer())
            {
                std::this_thread::sleep_for(std::chrono::milliseconds(1));
                continue;
            }
            std::cout << "ConnectServer is ok" << std::endl;
            continue;
        }
        for (int i = 0; i < data_size; i++)
        {
            buff_data += temp_buff[i];
        }
        int valid_start = 0, valid_size = 0;
        if (CheckValidData(buff_data, valid_start, valid_size))
        {
            DataProcessing(buff_data.substr(valid_start, valid_size));
            buff_data = buff_data.substr(valid_start + valid_size);
        }
        else
        {
            continue;
        }
    }
    delete []temp_buff;
}

void TcpClient::DataProcessing(const std::string &data)
{
    std::cout << "tcp data : " << data.c_str() << std::endl;
}

}
