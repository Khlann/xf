#ifndef TCPCLIENT_H
#define TCPCLIENT_H
#include <string>
#include <thread>

namespace COMMON{

class TcpClient
{
public:
    TcpClient();
    TcpClient(std::string &server_ip, int port);
    virtual ~TcpClient();

public:
    bool Start();
    void SetServerIP(std::string &server_ip);
    void SetServerPort(int port);
    void SetBuffSize(int size);
    bool ConnectServer();
    bool IsConnectServer();
    bool SendData(const char *data, int size);
    virtual void DataProcessing(const std::string &data);
    virtual bool CheckValidData(std::string &data, int &valid_start, int &valid_size);

private:
    void Stop();
    void CommThread();
    bool SetBlockOpt(int m_fd,bool blocked);

private:
    bool bISConnect_;
    std::thread thComm_;
    bool bIsStop_;
    int iSockfd_;
    std::string strServerIP_;
    int iPort_;
    int iBuffSize_;
};

}
#endif // TCPCLIENT_H
