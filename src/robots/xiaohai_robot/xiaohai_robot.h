#ifndef XIAOHAI_ROBOT_H
#define XIAOHAI_ROBOT_H
#include "work_base.h"
#include "central_server_tcp.h"
#include "common/ini/iniconfig.h"
#include "component/robot_arm_device/dz_robot_arm/dz_robot_arm.h"
#include "component/chassis_device/yixin_chassis_device/yixin_chassis.h"
#include <queue>

namespace ROBOTS {

typedef std::function<void(void)> ROBOT_WORK_FUN_VOID;

enum RobotStateType
{
    // ----系统状态----
    System_Uninitialized = 0,   //  未初始化
    System_Ready = 1,           //  准备就绪
    System_Error = 2,           //  错误
    System_Pausing = 3,         //  暂停中
    System_Resuming = 4,        //  恢复中
    System_Tasksing = 5         //  任务中
};

class RobotState
{
public:
    RobotState(){}
    ~RobotState(){}
public:
    int iRobotId_;

};

class XiaoHaiRobot : public COMMON::WorkBase
{
public:
    XiaoHaiRobot();
    ~XiaoHaiRobot();

    void Init();
    void CentralServerCallBack(const nlohmann::json& json_data);
    void WorkFun();
    void UpdateDeviceData();
    bool MoveChassis(int station_id);
    bool MoveArm(std::vector<float> tcp_pose);
    bool ArmReachTargetPose(std::vector<float> tcp_pose);
    long long GetTime();
    // virtual bool TaskScheduler(nlohmann::json &task_data);   // 任务调度
    void System_Uninitialized();
    void System_Ready();
    void System_Error();
    void System_Pausing();
    void System_Resuming();
    void System_Tasksing();

public:
    COMMON::CentralServerTcp CentralServer_;
    // std::queue<nlohmann::json> quQueryTasks_;// 机器人 查询任务
    std::queue<nlohmann::json> quProcessTasks_;// 机器人 流程任务
    std::unordered_map<int, ROBOT_WORK_FUN_VOID> umapWorkFun_;  // 哈希表，将每个状态和它所对应的函数绑定起来
    RobotStateType CurrentRobotStateType_;
    RobotState CurrentRobotState_;
    COMPONENT::DZ_RobotArm RobotArm_; //   机械臂
    COMPONENT::YiXinChassis RobotChassis_;  // 底盘

    // 底盘移动说明
    int iChassisTagetID_;
    bool bChassisMoveing_;

    // 机械臂移动说明
    std::vector<float> vecArmTagetPose_;
    long long llArmMoveTime_;   // 记录机械臂移动时间
    bool bArmMoveing_;
    // 气体检测
    bool bGasDetection_;
    long long llGasDetectionTime_;   // 记录气体检测时间
    // 辐射检测
    bool bRadiationDetection_;
    long long llRadiationDetectionTime_;   // 记录辐射检测时间
};


}    // namespace ROBOTS
#endif