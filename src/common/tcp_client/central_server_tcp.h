#ifndef CENTRAL_SERVER_H
#define CENTRAL_SERVER_H
#include "tcp_client.h"
#include <functional>
#include <nlohmann/json.hpp>

namespace COMMON{

typedef std::function<void(const nlohmann::json&)> TCP_CALLBACK_FUN;

class CentralServerTcp : public TcpClient
{
public:
    CentralServerTcp(TCP_CALLBACK_FUN callback);
    ~CentralServerTcp();

    void DataProcessing(const std::string &data);
    bool CheckValidData(std::string &data, int &valid_start, int &valid_size);
    void DataEncapsulation(std::string &data, nlohmann::json &json_obj);
private:
    uint8_t crc8(const uint8_t *data, int size);

    TCP_CALLBACK_FUN pCallBack_;
};

}   //  namespace COMMON
#endif