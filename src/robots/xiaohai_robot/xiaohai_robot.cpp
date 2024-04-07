#include "xiaohai_robot.h"

namespace ROBOTS {

XiaoHaiRobot::XiaoHaiRobot()
: COMMON::WorkBase(COMMON::WhileType::TIME)
, CentralServer_(std::bind(&XiaoHaiRobot::CentralServerCallBack, this, std::placeholders::_1))

{
    Init();
    std::string strIP = "192.168.1.219";
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
    umapWorkFun_.insert(std::make_pair(RobotStateType::System_Uninitialized, std::bind(&XiaoHaiRobot::System_Uninitialized, this)));
    umapWorkFun_.insert(std::make_pair(RobotStateType::System_Ready, std::bind(&XiaoHaiRobot::System_Ready, this)));
    umapWorkFun_.insert(std::make_pair(RobotStateType::System_Error, std::bind(&XiaoHaiRobot::System_Error, this)));
    umapWorkFun_.insert(std::make_pair(RobotStateType::System_Pausing, std::bind(&XiaoHaiRobot::System_Pausing, this)));
    umapWorkFun_.insert(std::make_pair(RobotStateType::System_Resuming, std::bind(&XiaoHaiRobot::System_Resuming, this)));

    CurrentRobotStateType_ = RobotStateType::System_Uninitialized;
    
    // 读配置文件
    inifile::IniFile ini_file;
    ini_file.Load("./config/robot_arm.ini");
    // 初始化 机器人
    ini_file.GetIntValue("RobotInfo", "RobotID", &CurrentRobotState_.iRobotId_);
    
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
    // 初始化 气体 传感器
    
    // 初始化 辐射 传感器
    
    // 初始化 测距 传感器
    
    // 初始化 称重 传感器

    CurrentRobotStateType_ = RobotStateType::System_Ready;
}

void XiaoHaiRobot::CentralServerCallBack(const nlohmann::json& json_data)
{
    quProcessTasks_.push(json_data);
    return;
}

void XiaoHaiRobot::UpdateDeviceData()
{
    // 底盘
    if (bChassisMoveing_ && iChassisTagetID_ == RobotChassis_.ChassisState_.iCurrentStationID_)
    {
        bChassisMoveing_ = false;
        // 回复 底盘已到达
        nlohmann::json json_obj;
        json_obj["type"] = 3500;    // 小海回复
        json_obj["robot_type"] = "AM_Robot";
        json_obj["robot_id"] = CurrentRobotState_.iRobotId_;
        json_obj["request_type"] = 3001; 
        json_obj["task_state"] = 0; 
        json_obj["chassis_info"]["station_id"] = RobotChassis_.ChassisState_.iCurrentStationID_; 
        json_obj["chassis_info"]["x"] = RobotChassis_.ChassisState_.dX_; 
        json_obj["chassis_info"]["y"] = RobotChassis_.ChassisState_.dY_; 
        json_obj["chassis_info"]["angle"] = RobotChassis_.ChassisState_.dAngle_;
        CentralServer_.SendJsonData(json_obj);
    }

    // 机械臂
    if (bArmMoveing_ && (RobotArm_.RobotArmState_.iInpos_ == 1))
    {
        if (ArmReachTargetPose(vecArmTagetPose_))
        {   // 到达位置
            bArmMoveing_ = false;
            // 回复 机械臂已到达
            nlohmann::json json_obj;
            json_obj["type"] = 3500;    // 小海回复
            json_obj["robot_type"] = "AM_Robot";
            json_obj["robot_id"] = CurrentRobotState_.iRobotId_;
            json_obj["request_type"] = 3002; 
            json_obj["task_state"] = 0; 
            json_obj["arm_info"]["x"] = RobotArm_.RobotArmState_.dTcp_X; 
            json_obj["arm_info"]["y"] = RobotArm_.RobotArmState_.dTcp_Y; 
            json_obj["arm_info"]["z"] = RobotArm_.RobotArmState_.dTcp_Z; 
            json_obj["arm_info"]["rx"] = RobotArm_.RobotArmState_.dTcp_Rx; 
            json_obj["arm_info"]["ry"] = RobotArm_.RobotArmState_.dTcp_Ry; 
            json_obj["arm_info"]["rz"] = RobotArm_.RobotArmState_.dTcp_Rz; 
            CentralServer_.SendJsonData(json_obj);
        }
    }

}

void XiaoHaiRobot::WorkFun()
{
    // 获取状态
    UpdateDeviceData();

    // 发送自身的状态数据
    nlohmann::json json_obj;
    json_obj["type"] = 3000;    // 小海心跳包
    json_obj["robot_type"] = "AM_Robot";
    json_obj["robot_id"] = CurrentRobotState_.iRobotId_;
    json_obj["chassis_info"]["station_id"] = RobotChassis_.ChassisState_.iCurrentStationID_; 
    json_obj["chassis_info"]["x"] = RobotChassis_.ChassisState_.dX_; 
    json_obj["chassis_info"]["y"] = RobotChassis_.ChassisState_.dY_; 
    json_obj["chassis_info"]["angle"] = RobotChassis_.ChassisState_.dAngle_; 
    CentralServer_.SendJsonData(json_obj);
    
    // 执行状态
    umapWorkFun_[CurrentRobotStateType_]();
}

// 移动底盘
bool XiaoHaiRobot::MoveChassis(int station_id)
{
    bChassisMoveing_ = true;
    iChassisTagetID_ = station_id;
    RobotChassis_.Move(station_id);
    return true;
}

bool XiaoHaiRobot::MoveArm(std::vector<float> tcp_pose)
{
    bArmMoveing_ = true;
    vecArmTagetPose_ = tcp_pose;
    llArmMoveTime_ = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
    return RobotArm_.MoveRobotArm(tcp_pose);
}

bool XiaoHaiRobot::ArmReachTargetPose(std::vector<float> tcp_pose)
{
    if ( ((tcp_pose[0] - 2 <= RobotArm_.RobotArmState_.dTcp_X) && (tcp_pose[0] + 2 >= RobotArm_.RobotArmState_.dTcp_X))
    &&((tcp_pose[1] - 2 <= RobotArm_.RobotArmState_.dTcp_Y) && (tcp_pose[1] + 2 >= RobotArm_.RobotArmState_.dTcp_Y))
    &&((tcp_pose[2] - 2 <= RobotArm_.RobotArmState_.dTcp_Z) && (tcp_pose[2] + 2 >= RobotArm_.RobotArmState_.dTcp_Z))
    &&((tcp_pose[3] - 2 <= RobotArm_.RobotArmState_.dTcp_Rx) && (tcp_pose[3] + 2 >= RobotArm_.RobotArmState_.dTcp_Rx))
    &&((tcp_pose[4] - 2 <= RobotArm_.RobotArmState_.dTcp_Ry) && (tcp_pose[4] + 2 >= RobotArm_.RobotArmState_.dTcp_Ry))
    &&((tcp_pose[5] - 2 <= RobotArm_.RobotArmState_.dTcp_Rz) && (tcp_pose[5] + 2 >= RobotArm_.RobotArmState_.dTcp_Rz)) )
    {
        return true;
    }
    return false;
}

long long XiaoHaiRobot::GetTime()
{
    return std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
}

void XiaoHaiRobot::System_Uninitialized()
{

}

void XiaoHaiRobot::System_Ready()
{
    if (!quProcessTasks_.empty())
    {
        auto json = quProcessTasks_.front();
        int task_type = json["type"];
        switch (task_type)
        {
        case 3001:  // 移动底盘
        {
            MoveChassis(json["chassis_id"]);
            break;
        }
        case 3002:  // 移动机械臂
        {
            std::vector<float> tcp_pose(6, 0.0);
            tcp_pose[0] = json["arm_info"]["x"];
            tcp_pose[1] = json["arm_info"]["y"];
            tcp_pose[2] = json["arm_info"]["z"];
            tcp_pose[3] = json["arm_info"]["rx"];
            tcp_pose[4] = json["arm_info"]["ry"];
            tcp_pose[5] = json["arm_info"]["rz"];
            MoveArm(tcp_pose);
            break;
        }
        case 3003:  // 气体检测
        {
            // 触发气体检测
            bGasDetection_ = true;
            llGasDetectionTime_ = GetTime();
            break;
        }
        case 3004:  // 辐射检测
        {
            // 触发辐射检测
            bRadiationDetection_ = true;
            llRadiationDetectionTime_ = GetTime();
            break;
        }
        case 3005:  // 体积、重量测量
        {
            // 读取激光值
            break;
        }
        case 3006:  // 获取照片
        {
            // 获取照片
            break;
        }
        case 3007:  // 语音播报
        {
            // 语音播报
            break;
        }
        default:
            break;
        }
    }
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

void XiaoHaiRobot::System_Tasksing()
{

}

}// namespace ROBOTS
