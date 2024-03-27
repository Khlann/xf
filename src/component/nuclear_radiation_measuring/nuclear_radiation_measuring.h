#ifndef NUCLEAR_RADIATION_MEASURING_H
#define NUCLEAR_RADIATION_MEASURING_H
#include <thread>
#include "work_base.h"
#include "common/serial_communication/serial_communication.h"


namespace COMPONENT{
class NuclearRadiationMeasuring
{
public:
    NuclearRadiationMeasuring(std::string device_name, int baud_rate);
    ~NuclearRadiationMeasuring();

public:
    double Get_Radiation_Value();
    
private:
    void scanFun();

private:
    COMMON::SerialCommunication Device_;
    std::string strBufferData_;
    double value_;

};
}
#endif 
