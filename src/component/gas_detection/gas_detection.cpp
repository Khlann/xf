#include "gas_detection.h"
#include <iostream>

namespace COMPONENT{

GasDetection::GasDetection(std::string device_name, int baud_rate)
    : Device_(device_name, baud_rate)
{
}

GasDetection::~GasDetection()
{

}

// bool GasDetection::send_once()
// {
//     if (!Device_.IsCommunication())
//     {
//         return false;
//     }
//     // 01 03 00 00 00 04 CRC1 CRC2
//     char send_data[] = {static_cast<char>(0x01), static_cast<char>(0x03), static_cast<char>(0x00)
//                         , static_cast<char>(0x00), static_cast<char>(0x00), static_cast<char>(0x04)
//                         , static_cast<char>(0x64), static_cast<char>(0x04)};
//     Device_.WriteData(std::string(send_data, 8));
//     return true;
// }


void GasDetection::gasFun()
{
    if (!Device_.IsCommunication())
    {
        Device_.EstablishCommunication();
    }
    else
    {
        std::string get_data;
        Device_.ReadData(get_data);
        strBufferData_ += get_data;
        // 01 03 08 数1 数2 数3 数4 crc1 crc2
        while (1)
        {
            int head_index = strBufferData_.find(0x01);   //接收数据的帧头 01
            if ((head_index > -1) && (head_index + 13 <= (int)strBufferData_.size()))
            {
                // double iconcentration1 = 0.0;
                // double iconcentration2 = 0.0;
                // double iconcentration3 = 0.0;
                // double iconcentration4 = 0.0;
                // iconcentration1 = (double)( ((strBufferData_[head_index + 4] & 0xFF) << 8)
                //                  | (strBufferData_[head_index + 5] & 0xFF) );
                // iconcentration2 = (double)( ((strBufferData_[head_index + 6] & 0xFF) << 8)
                //                  | (strBufferData_[head_index + 7] & 0xFF) );     
                // iconcentration3 = (double)( ((strBufferData_[head_index + 8] & 0xFF) << 8)
                //                  | (strBufferData_[head_index + 9] & 0xFF) );  
                // iconcentration4 = (double)( ((strBufferData_[head_index + 10] & 0xFF) << 8)
                //                  | (strBufferData_[head_index + 11] & 0xFF) );                              
                // concentration_.push_back(iconcentration1,iconcentration2,iconcentration3,iconcentration4)
                strBufferData_ = strBufferData_.substr(head_index + 13);
            }
        }
    }
}

}
