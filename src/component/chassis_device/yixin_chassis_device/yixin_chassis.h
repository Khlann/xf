#ifndef YI_XIN_CHASSIS_H
#define YI_XIN_CHASSIS_H
#include "common/udp_client/udp_client.h"
#include "common/work_base/work_base.h"

namespace COMPONENT{

class YiXinChassisState
{
public:
    YiXinChassisState()
    {
        dX_ = 0.0;
        dY_ = 0.0;
        dAngle_ = 0.0;
        iCurrentStationID_ = 0;
        iState_ = 0;
    }
    ~YiXinChassisState(){}
public:
    double dX_;
    double dY_;
    double dAngle_;
    int iCurrentStationID_;
    int iState_;
};

class YiXinChassis  : public COMMON::WorkBase
{

public:
    YiXinChassis(/* args */);
    ~YiXinChassis();
public:
    void UdpDataCallBack(std::string& data);
    void WorkFun();
    void Move(int id);
    void DataAnalysis(std::string& data);
public:
    COMMON::UDPClient UDPClient_;
    YiXinChassisState ChassisState_;
};

}
#endif