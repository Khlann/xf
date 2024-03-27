#include "serial_communication.h"
#include <fcntl.h>
#include <termios.h>
#include <unistd.h>
#include <string.h>

namespace COMMON{
SerialCommunication::SerialCommunication(std::string port_name, int baud_rate)
{
    strPortName_ = port_name;
    iBaudRate_ = baud_rate;
    iFd_ = -1;
    pBuffer_ = nullptr;
}

SerialCommunication::~SerialCommunication()
{
    StopCommunication();
    if (pBuffer_)
    {
        delete pBuffer_;
        pBuffer_ = nullptr;
    }
}

bool SerialCommunication::EstablishCommunication()
{
    if (pBuffer_ == nullptr)
    {
        pBuffer_ = new char[1024];
    }

    iFd_ = open(strPortName_.c_str(), O_RDWR | O_NOCTTY | O_NDELAY);
    if (iFd_ == -1)
    {
        return false;
    }
    else
    {
        // 配置串口参数
        struct termios options;
        tcgetattr(iFd_, &options);
        cfsetispeed(&options, iBaudRate_);
        cfsetospeed(&options, iBaudRate_);
        options.c_cflag |= ( CLOCAL | CREAD );
        options.c_cflag &= ~CSIZE;
        options.c_cflag &= ~CRTSCTS;
        options.c_cflag |= CS8;
        options.c_cflag &= ~CSTOPB;
        options.c_iflag |= IGNPAR;
        options.c_iflag &= ~(ICRNL | IXON);
        options.c_oflag = 0;
        options.c_lflag = 0;
        tcsetattr(iFd_, TCSANOW, &options);
    }
    return true;
}

void SerialCommunication::StopCommunication()
{
    if (iFd_ != -1)
    {
        close(iFd_);
        iFd_ = -1;
    }
}

bool SerialCommunication::IsCommunication()
{
    if (iFd_ != -1)
    {
        return true;
    }
    return false;
}

void SerialCommunication::WriteData(const std::string& data)
{
    if (iFd_ != -1)
    {
        write(iFd_, data.c_str(), data.size());
    }
}

void SerialCommunication::ReadData(std::string& data)
{
    if (iFd_ != -1)
    {
        memset(pBuffer_, 0, 1024);
        ssize_t bytesRead = read(iFd_, pBuffer_, 1024);
        if (bytesRead > 0)
        {
            data.assign(pBuffer_, bytesRead);
        }
    }
}

}
