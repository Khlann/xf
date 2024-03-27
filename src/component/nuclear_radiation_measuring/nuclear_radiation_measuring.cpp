#include "nuclear_radiation_measuring.h"
#include <iostream>

namespace COMPONENT{

double NuclearRadiationMeasuring::Get_Radiation_Value()
{
    return value_;
}


NuclearRadiationMeasuring::~NuclearRadiationMeasuring()
{
    Device_.StopCommunication();
}


// bool NuclearRadiationMeasuring::send_request()
// {
//     if (!Device_.IsCommunication())
//     {
//         return false;
//     }
//     // 01 03 00 36 00 01 64 04
//     char send_data[] = {static_cast<char>(0x01), static_cast<char>(0x03), static_cast<char>(0x00)
//                         , static_cast<char>(0x36), static_cast<char>(0x00), static_cast<char>(0x01)
//                         , static_cast<char>(0x64), static_cast<char>(0x04)};
//     Device_.WriteData(std::string(send_data, 8));
//     return true;
// }



void NuclearRadiationMeasuring::scanFun()
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

        // 01 03 02 数1 数2 crc1 crc2
        while (1)
        {
            int head_index = strBufferData_.find(0x01);   //接收数据的帧头 01
            if ((head_index > -1) && (head_index + 7 <= (int)strBufferData_.size()))
            {
                double ivalue =0.0;
                ivalue = (double)( ((strBufferData_[head_index + 4] & 0xFF) << 8)
                                 | (strBufferData_[head_index + 5] & 0xFF) );
                value_ = ivalue;
                strBufferData_ = strBufferData_.substr(head_index + 7);
            }
        }
    }
}

}
