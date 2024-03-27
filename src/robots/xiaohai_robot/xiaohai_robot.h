#ifndef XIAOHAI_ROBOT_H
#define XIAOHAI_ROBOT_H
#include "work_base.h"
#include "central_server_tcp.h"
#include "common/ini/iniconfig.h"
#include "component/robot_arm_device/dz_robot_arm/dz_robot_arm.h"
#include "common/ini/iniconfig.h"
#include <queue>

namespace ROBOTS {

typedef std::function<void(void)> ROBOT_WORK_FUN_VOID;

enum RobotState
{
    // ----系统状态----
    System_Uninitialized = 0,   //  未初始化
    System_Ready = 1,           //  准备就绪
    System_Error = 2,           //  错误
    System_Pausing = 3,         //  暂停中
    System_Resuming = 4,        //  恢复中
    // ----任务状态----
    // ToMissionPlatformPoint = 100,    // 前往任务月台点
    // ArmToSpecifyingPose = 101, // 机械臂 移动到 指定姿态
    // GetImage = 102  // 获取照片
};

class XiaoHaiRobot : public COMMON::WorkBase
{
public:
    XiaoHaiRobot();
    ~XiaoHaiRobot();

    void Init();
    void CentralServerCallBack(const nlohmann::json& json_data);
    void WorkFun();
    // virtual bool TaskScheduler(nlohmann::json &task_data);   // 任务调度
    void System_Uninitialized();
    void System_Ready();
    void System_Error();
    void System_Pausing();
    void System_Resuming();

public:
    COMMON::CentralServerTcp CentralServer_;
    std::queue<nlohmann::json> quQueryTasks_;// 机器人 查询任务
    std::queue<nlohmann::json> quProcessTasks_;// 机器人 流程任务
    std::unordered_map<int, ROBOT_WORK_FUN_VOID> umapWorkFun_;  // 哈希表，将每个状态和它所对应的函数绑定起来
    RobotState CurrentRobotState_;

    COMPONENT::DZ_RobotArm RobotArm_; //   机械臂
};


}    // namespace ROBOTS
#endif