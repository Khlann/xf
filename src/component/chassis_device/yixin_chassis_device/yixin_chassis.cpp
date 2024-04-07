#include "yixin_chassis.h"

namespace COMPONENT{

YiXinChassis::YiXinChassis()
: COMMON::WorkBase(COMMON::WhileType::TIME)
, UDPClient_("192.168.31.10", 9331, std::bind(&YiXinChassis::UdpDataCallBack, this, std::placeholders::_1))
{
    COMMON::WorkBase::SetSleep(100);
    COMMON::WorkBase::ExecutionThread();
}

YiXinChassis::~YiXinChassis()
{
}

uint16_t PY_CRC_16_T8_X25_i(uint8_t *di, uint32_t len)
{
	uint16_t crc_poly = 0x8408; //Bit sequence inversion of 0x1021
	uint16_t data_t = 0xFFFF; //CRC register

    for(uint32_t i = 0; i < len; i++)
    {
    	data_t ^= di[i]; //8-bit data

        for (uint8_t j = 0; j < 8; j++)
        {
            if (data_t & 0x0001)
            	data_t = (data_t >> 1) ^ crc_poly;
            else
            	data_t >>= 1;
        }
    }
    return data_t ^ 0xFFFF;
}

void uint32ToLittleEndianString(uint32_t value, u_char* buffer) 
{
    buffer[0] = static_cast<u_char>(value & 0xFF);         // 低字节
    buffer[1] = static_cast<u_char>((value >> 8) & 0xFF);  // 第二个字节
    buffer[2] = static_cast<u_char>((value >> 16) & 0xFF); // 第三个字节
    buffer[3] = static_cast<u_char>((value >> 24) & 0xFF); // 高字节
}

uint32_t littleEndianStringToUint32(const char* buffer) 
{
    uint32_t value = 0;
    value |= static_cast<uint32_t>(buffer[0] & 0xFF);         // 低字节
    value |= static_cast<uint32_t>((buffer[1] & 0xFF) << 8);  // 第二个字节
    value |= static_cast<uint32_t>((buffer[2] & 0xFF) << 16); // 第三个字节
    value |= static_cast<uint32_t>((buffer[3] & 0xFF) << 24); // 高字节
    return value;
}

float bytesToFloat(const uint8_t* bytes) {
    // 使用类型转换将字节解释为float
    float result;
    std::memcpy(&result, bytes, sizeof(float));
    return result;
}

void YiXinChassis::DataAnalysis(std::string& data)
{

}

void YiXinChassis::UdpDataCallBack(std::string& data)
{
    if (data.size() < 8)
    {
        return;
    }    
    // 消息类型
    if (data[2] == 0x03)    // 读回复
    {
        if (data[4] == 0x4c && data[5] == 0x02)
        {   // 全局 ID
            uint32_t temp_id = littleEndianStringToUint32(&data.c_str()[8]);
            ChassisState_.iCurrentStationID_ = temp_id;
        }
        else if (data[4] == 0x50 && data[5] == 0x02)
        {   // 设置运行
            // uint8_t temp = data.c_str()[8];
        }
        else if (data[4] == 0x52 && data[5] == 0x02)
        {   // 节点序号 0×252
            // uint8_t temp = data.c_str()[8];
        }
        else if (data[4] == 0x53 && data[5] == 0x02)
        {   // 路线类型 0×253
            // uint8_t temp = data.c_str()[8];
        }
        else if (data[4] == 0x56 && data[5] == 0x02)
        {   // 节点属性 0×256
            // uint8_t temp = data.c_str()[8];
        }
        else if (data[4] == 0x57 && data[5] == 0x02)
        {   // 动作编号 0×257
            // uint8_t temp = data.c_str()[8];
        }
        else if (data[4] == 0x60 && data[5] == 0x02)
        {   // x坐标 0×260
            float temp_x = bytesToFloat((uint8_t*)&data.c_str()[8]);
            ChassisState_.dX_ = temp_x;
        }
        else if (data[4] == 0x64 && data[5] == 0x02)
        {   // y坐标 0×264
            float temp_y = bytesToFloat((uint8_t*)&data.c_str()[8]);
            ChassisState_.dX_ = temp_y;
        }
        else if (data[4] == 0x68 && data[5] == 0x02)
        {   // Theta角度 0×268
            float temp_Theta = bytesToFloat((uint8_t*)&data.c_str()[8]);
            ChassisState_.dAngle_ = temp_Theta;
        }
        else if (data[4] == 0x6c && data[5] == 0x02)
        {   // 高度值 0×26c
            // float temp_h = bytesToFloat((uint8_t*)&data.c_str()[8]);
        }
        else if (data[4] == 0x90 && data[5] == 0x02)
        {   // 任务字 0×290
            // std::string strTemp;
            // data[6];
        }
        else
        {
            std::cout<< " 不明消息 " << data[4] << " " << data[5] << std::endl;
        }
    }
    else if (data[2] == 0x04)   // 写回复
    {
        ; // 暂时忽略写回复的消息
    }
    
}

void YiXinChassis::Move(int id)
{
    // 设置终点 31 07 02  01  d4  03  04 00 01 00 00 00
    u_char cTarget[12] = {0};
    cTarget[2] = 0x02;
    cTarget[3] = 0x01;
    cTarget[4] = 0xd4;
    cTarget[5] = 0x03;
    cTarget[6] = 0x04;
    cTarget[7] = 0x00;
    u_int32_t u32_id = id;
    uint32ToLittleEndianString(u32_id, &cTarget[8]);
    uint16_t crc = PY_CRC_16_T8_X25_i(&cTarget[2], 10);
    cTarget[0] = static_cast<u_char>((crc >> 8) & 0xFF);    // 高位
    cTarget[1] = static_cast<u_char>(crc & 0xFF);   // 低位
    UDPClient_.sendMessage((char*)cTarget, 12);

    // 设置3，则AGV开始自身搜索路线运行
    u_char cRunMove[9] = {0};
    cRunMove[2] = 0x02;
    cRunMove[3] = 0x01;
    cRunMove[4] = 0x50;
    cRunMove[5] = 0x02;
    cRunMove[6] = 0x01;
    cRunMove[7] = 0x00;
    cRunMove[8] = 0x03;

    crc = PY_CRC_16_T8_X25_i(&cRunMove[2], 7);
    cRunMove[0] = static_cast<u_char>((crc >> 8) & 0xFF);   // 高位
    cRunMove[1] = static_cast<u_char>(crc & 0xFF);  // 低位
    UDPClient_.sendMessage((char*)cRunMove, 9);
}

void YiXinChassis::WorkFun()
{
    // crcH crcL  命令  序号   地址  地址  长度  长度  数据
    //  0     1    2     3     4    5     6    7   8-n
    // 全局ID
    char query_data[8] = {0};
    // 查询 x b7 b0 01 01 04 01 04 00
    query_data[0] = 0xc5; query_data[1] = 0x5c; query_data[2] = 0x01; query_data[3] = 0x01;
    query_data[4] = 0x00; query_data[5] = 0x01; query_data[6] = 0x04; query_data[7] = 0x00;
    UDPClient_.sendMessage(query_data, 8);
    // 查询 y
    query_data[0] = 0xb7; query_data[1] = 0xb0; query_data[2] = 0x01; query_data[3] = 0x01;
    query_data[4] = 0x04; query_data[5] = 0x01; query_data[6] = 0x04; query_data[7] = 0x00;
    UDPClient_.sendMessage(query_data, 8);
    // 查询 theta角度
    query_data[0] = 0x20; query_data[1] = 0x84; query_data[2] = 0x01; query_data[3] = 0x01;
    query_data[4] = 0x08; query_data[5] = 0x01; query_data[6] = 0x04; query_data[7] = 0x00;
    UDPClient_.sendMessage(query_data, 8);
    // 电量百分比
    query_data[0] = 0x1f; query_data[1] = 0x33; query_data[2] = 0x01; query_data[3] = 0x01;
    query_data[4] = 0x3f; query_data[5] = 0x00; query_data[6] = 0x01; query_data[7] = 0x00;
    UDPClient_.sendMessage(query_data, 8);
    // Agv当前全局ID
    query_data[0] = 0xd9; query_data[1] = 0x57; query_data[2] = 0x01; query_data[3] = 0x01;
    query_data[4] = 0x48; query_data[5] = 0x02; query_data[6] = 0x04; query_data[7] = 0x00;
    UDPClient_.sendMessage(query_data, 8);
    // 当前速度
    query_data[0] = 0x10; query_data[1] = 0xd3; query_data[2] = 0x01; query_data[3] = 0x01;
    query_data[4] = 0x20; query_data[5] = 0x00; query_data[6] = 0x04; query_data[7] = 0x00;
    UDPClient_.sendMessage(query_data, 8);
    // 当前地图
    query_data[0] = 0x0d; query_data[1] = 0x46; query_data[2] = 0x01; query_data[3] = 0x01;
    query_data[4] = 0x20; query_data[5] = 0x03; query_data[6] = 0x10; query_data[7] = 0x00;
    UDPClient_.sendMessage(query_data, 8);
    // 当前运行状态
    query_data[0] = 0x8b; query_data[1] = 0x9a; query_data[2] = 0x01; query_data[3] = 0x01;
    query_data[4] = 0x11; query_data[5] = 0x02; query_data[6] = 0x01; query_data[7] = 0x00;
    UDPClient_.sendMessage(query_data, 8);
}

}