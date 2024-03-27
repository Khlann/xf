#ifndef GAS_DETECTION_H
#define GAS_DETECTION_H
#include <thread>
#include "work_base.h"
#include "common/serial_communication/serial_communication.h"


namespace COMPONENT{
class GasDetection
{
public:
    GasDetection(std::string device_name, int baud_rate);
    ~GasDetection();

// public:
    // double Get_gas_message();
    // void send_once();
private:
    void gasFun();

private:
    COMMON::SerialCommunication Device_;
    std::string strBufferData_;
    double concentration;
};
}
#endif 