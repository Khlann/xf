#ifndef DZ_ROBOT_ARM_H
#define DZ_ROBOT_ARM_H

#include "work_base.h"
#include "include/HR_Pro.h"

// #ifdef __cplusplus
// extern "C"
// {
// #endif

// #include "include/HR_Pro.h"

// #ifdef __cplusplus
// }
// #endif

namespace COMPONENT{

class RobotArmState
{
public:
    RobotArmState(){}
    ~RobotArmState(){}
public:
    int iCurFSM_;   // 机械臂状态
    std::string strCurFSM_;  // 机械臂状态 字符串
    bool bIsMotionDone_;     // 是否运动状态
    bool bIsBlendingDone_;   // 是否运动完成
    int iMovingState_;  // 运动状态
    int iEnableState_;  // 使能状态
    int iErrorState_;   // 错误状态
    int iErrorCode_;    // 错误码
    int iErrorAxis_;    // 错误轴ID
    int iBreaking_;     // 抱闸状态
    int iPause_;        // 暂停状态
    int iEmergencyStop_;// 急停状态
    int iSaftyGuard_;   // 安全光幕状态
    int iElectrify_;    // 上电状态
    int iIsConnectToBox_;   // 电箱连接状态
    int iBlendingDone_; //路点运动状态
    int iInpos_;        // 到位状态
};

class DZ_RobotArm : public COMMON::WorkBase
{
public:
    DZ_RobotArm();
    ~DZ_RobotArm();

    void WorkFun();

    bool MoveRobotArm(std::vector<float> arr);
    bool GrpStop();     // 停止运动
    bool GrpDisable();  // 下使能
    bool GrpInterrupt();// 暂停
    bool GrpContinue(); // 继续运动
    bool RunRobotArm(); // 运行机械臂
    bool Init(std::string ip, int port, int box_id, int robot_id);    //  初始化

private:
    std::string strIP_;
    int iPort_;
    int iBoxID_;
    int iRobotID_;
    bool bIsConnected_;

public:
    RobotArmState RobotArmState_;
};

}   // namespace COMPONENT
#endif