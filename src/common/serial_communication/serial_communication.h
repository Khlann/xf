#ifndef SERIALCOMMUNICATION_H
#define SERIALCOMMUNICATION_H
#include <string>

namespace COMMON{
class SerialCommunication
{
public:
    SerialCommunication(std::string port_name, int baud_rate);
    ~SerialCommunication();

    bool EstablishCommunication();
    void StopCommunication();
    bool IsCommunication();
    void WriteData(const std::string& data);
    void ReadData(std::string& data);

private:
    std::string strPortName_;
    int iBaudRate_;
    int iFd_;
    char *pBuffer_;
};
}

#endif // SERIALCOMMUNICATION_H
