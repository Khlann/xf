#include "central_server_tcp.h"
#include <iostream>

namespace COMMON {


CentralServerTcp::CentralServerTcp(TCP_CALLBACK_FUN callback)
: pCallBack_(nullptr)
{
    pCallBack_ = callback;
}

CentralServerTcp::~CentralServerTcp()
{
     pCallBack_ == nullptr;
}

bool JsonParse(std::string json_str, nlohmann::json &json_obj)
{
    try
    {
        // 解析 JSON 字符串
        json_obj = nlohmann::json::parse(json_str);
        if (!json_obj["robot_type"].is_string())
        {
            return false;
        }
        if (!json_obj["type"].is_number_integer())
        {
            return false;
        }
        if (!json_obj["robot_id"].is_number_integer())
        {
            return false;
        }
        if (!json_obj["tags"].is_number_integer())
        {
            return false;
        }
        // 输出有效的 JSON
        std::cout << "Valid JSON:" << std::endl
                  << json_obj.dump(4) << std::endl;
    }
    catch (const std::exception &e)
    {
        // 输出错误信息
        std::cout << "Error: " << e.what() << std::endl;
        return false;
    }
    return true;
}

void CentralServerTcp::DataEncapsulation(std::string &data, nlohmann::json &json_obj)
{
    data += 0xFE;
    data += 0xFF;
    int32_t size = (int32_t)(json_obj.dump().size());
    size += 1;  // 有一位校验码
    for (int i = 0; i < (int)sizeof(int32_t); ++i) 
    {
        unsigned char byte = (size >> (8 * i)) & 0xFF;
        data += byte;
    }
    data += json_obj.dump();
    data += crc8((const uint8_t *)json_obj.dump().c_str(), json_obj.dump().size());
}

// 数据处理
void CentralServerTcp::DataProcessing(const std::string &data)
{
    int iDataLength = data[3] << 8 | data[4] << 16 | data[5] << 24 | data[2];

    std::string strReplyData;   // 回复消息的字符串
    nlohmann::json jsonReplyData;   // 回复消息的json
    jsonReplyData["type"] = 2000;   // 回复消息类型
    jsonReplyData["date"] = std::chrono::duration_cast<std::chrono::milliseconds>(
            std::chrono::system_clock::now().time_since_epoch()).count();   // 回复消息时间
    jsonReplyData["robot_type"] = "";
    jsonReplyData["request_type"] = "";
    jsonReplyData["request_tags"] = "";
    jsonReplyData["request_state"] = 100;
    // 检查校验码
    uint8_t crc8_value = crc8((uint8_t *)(data.substr(6, iDataLength - 1).c_str()), iDataLength - 1);
    if (crc8_value == (uint8_t)(data[5 + iDataLength]))
    { // 校验码没有问题
        // 解析 json 数据
        // 先校验JSON数据的合理性，不然会异常退出
        std::string json_str;
        // 尝试解析 JSON
        nlohmann::json jsondata;
        if (JsonParse(data.substr(6, iDataLength - 1), jsondata))
        {   // 数据没有问题，可以直接访问
            jsonReplyData["robot_type"] = jsondata["robot_type"];
            jsonReplyData["request_type"] = jsondata["type"];
            jsonReplyData["request_tags"] = jsondata["tags"];
            jsonReplyData["request_state"] = 0;

            pCallBack_(jsondata);
        }
        else
        {   // 解析错误
            jsonReplyData["request_state"] = 2;
        }
    }
    else
    {   // 校验码 错误
        jsonReplyData["request_state"] = 3;
    }


    // 回复收到数据
    DataEncapsulation(strReplyData, jsonReplyData);
    // TcpServer_.SendData((int64_t)client_data.ClientInfo_.pClientBEv_, strReplyData);
}

uint8_t CentralServerTcp::crc8(const uint8_t *data, int size)
{
    uint8_t crc = 0x00;
    uint8_t poly = 0x07;
    int bit;
    while (size--)
    {
        crc ^= *data++;
        for (bit = 0; bit < 8; bit++)
        {
            if (crc & 0x80)
            {
                crc = (crc << 1) ^ poly;
            }
            else
            {
                crc <<= 1;
            }
        }
    }
    return crc;
}

bool CentralServerTcp::CheckValidData(std::string &data, int &valid_start, int &valid_size)
{
    int index_1 = data.find(0xFE);
    if ((index_1 >= 0) && ( static_cast<unsigned char>(data.c_str()[index_1 + 1]) == 0xff))
    { // 找到包头
        if ((index_1 + 8) >= (int)data.size())
        { // 报文长度适合
            // 解析长度
            int iDataLength = data[index_1 + 3] << 8 | data[index_1 + 4] << 16 | data[index_1 + 5] << 24 | data[index_1 + 2];
            if (index_1 + 6 + iDataLength <= (int)data.size())
            { // 报文长度适合
                valid_start = index_1;
                valid_size = iDataLength;
            }
        }
        else
        {
            return false;
        }
    }
    else
    {
        return false;
    }

    return true;
}

}