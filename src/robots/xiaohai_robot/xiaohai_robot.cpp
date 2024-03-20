#include "xiaohai_robot.h"

namespace ROBOTS {

XiaoHaiRobot::XiaoHaiRobot()
: COMMON::WorkBase(COMMON::WhileType::TIME)
, CentralServer_(std::bind(&XiaoHaiRobot::CentralServerCallBack, this, std::placeholders::_1))
{
    Init();

    WorkBase::SetSleep(100);
    WorkBase::ExecutionThread();

    std::string strIP = "127.0.0.1";
    CentralServer_.SetServerIP(strIP);
    CentralServer_.SetServerPort(13304);
    CentralServer_.Start();
}

XiaoHaiRobot::~XiaoHaiRobot()
{
}

// 初始化 函数
void XiaoHaiRobot::Init()
{
    // 初始化 底盘
    // 初始化 机械臂
    // 初始化 相机
    // 初始化 XXX传感器
}

void XiaoHaiRobot::CentralServerCallBack(const nlohmann::json& json_data)
{
    if (json_data["request_type"] == 1000)
    {   // 状态查询
        quQueryTasks_.push(json_data);
    }
    else
    {
        quProcessTasks_.push(json_data);
    }
    return;
}

void XiaoHaiRobot::WorkFun()
{
    // 执行状态

}

}// namespace ROBOTS
