#include "xiaohai_robot.h"

namespace ROBOTS {

XiaoHaiRobot::XiaoHaiRobot()
: COMMON::WorkBase(COMMON::WhileType::TIME)
, CentralServer_(std::bind(&XiaoHaiRobot::CentralServerCallBack, this, std::placeholders::_1))

{
    Init();
    std::string strIP = "127.0.0.1";
    CentralServer_.SetServerIP(strIP);
    CentralServer_.SetServerPort(13304);
    CentralServer_.Start();

    WorkBase::SetSleep(100);
    WorkBase::ExecutionThread();
}

XiaoHaiRobot::~XiaoHaiRobot()
{
}

// 初始化 函数
void XiaoHaiRobot::Init()
{
    umapWorkFun_.insert(std::make_pair(RobotState::System_Uninitialized, std::bind(&XiaoHaiRobot::System_Uninitialized, this)));
    umapWorkFun_.insert(std::make_pair(RobotState::System_Ready, std::bind(&XiaoHaiRobot::System_Ready, this)));
    umapWorkFun_.insert(std::make_pair(RobotState::System_Error, std::bind(&XiaoHaiRobot::System_Error, this)));
    umapWorkFun_.insert(std::make_pair(RobotState::System_Pausing, std::bind(&XiaoHaiRobot::System_Pausing, this)));
    umapWorkFun_.insert(std::make_pair(RobotState::System_Resuming, std::bind(&XiaoHaiRobot::System_Resuming, this)));

    CurrentRobotState_ = RobotState::System_Uninitialized;
    
    // 读配置文件
    inifile::IniFile ini_file;
    ini_file.Load("./config/robot_arm.ini");
    /// 初始化 底盘
    
    
    /// 初始化 机械臂
    int robot_id = -1;
    int box_id = -1;
    std::string robot_arm_ip;
    int port = -1;
    ini_file.GetIntValue("RobotArm0", "RobotID", &robot_id);
    ini_file.GetIntValue("RobotArm0", "BoxID", &robot_id);
    ini_file.GetStringValue("RobotArm0", "RobotArmIP", &robot_arm_ip);
    ini_file.GetIntValue("RobotArm0", "RobotArmPort", &port);
    RobotArm_.Init(robot_arm_ip, port, box_id, robot_id);
    RobotArm_.RunRobotArm();    //  运行机械臂
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
    umapWorkFun_[CurrentRobotState_]();
}

void XiaoHaiRobot::System_Uninitialized()
{

}

void XiaoHaiRobot::System_Ready()
{

}

void XiaoHaiRobot::System_Error()
{

}

void XiaoHaiRobot::System_Pausing()
{

}

void XiaoHaiRobot::System_Resuming()
{

}

}// namespace ROBOTS
