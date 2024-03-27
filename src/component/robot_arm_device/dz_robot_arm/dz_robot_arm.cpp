#include "dz_robot_arm.h"
#include <iostream>

namespace COMPONENT{

DZ_RobotArm::DZ_RobotArm()
: COMMON::WorkBase(COMMON::WhileType::TIME)
{

}

DZ_RobotArm::~DZ_RobotArm()
{

}

void DZ_RobotArm::WorkFun()
{
    bIsConnected_ = HRIF_IsConnected(iBoxID_);
    if (!bIsConnected_)
    {   // 还没有连接电箱
        if (HRIF_Connect(iBoxID_, strIP_.c_str(), iPort_) != 0) //连接机器人服务器
        {
            std::cout << "HRIF_Connect调用 失败!" << std::endl;
            return;
        }
        else
        {
           std::cout << "HRIF_Connect调用 成功!" << std::endl;
        }
    }
    // 获取机械臂的状态机
    int nRet= HRIF_ReadCurFSM(iBoxID_, iRobotID_, RobotArmState_.iCurFSM_, RobotArmState_.strCurFSM_);
    if (nRet != 0)
    {
        std::cout << "HRIF_ReadCurFSM调用 失败! -> " << nRet << std::endl;
        return;
    }

    switch (RobotArmState_.iCurFSM_)
    {
        case 24:    // 机器人去使能
        {
            HRIF_GrpEnable(iBoxID_, iRobotID_);  // 上使能
            break;
        }
        case 22:    // 机器人错误
        {
            HRIF_GrpReset(iBoxID_, iRobotID_);   // 机器人复位
            break;
        }
        case 5:     // 急停
        {
            HRIF_GrpReset(iBoxID_, iRobotID_);   // 机器人复位
            break;
        }
        case 14:     // 控制器已处于未初始化状态
        {
            HRIF_Connect2Controller(iBoxID_);   // 连接控制器
            break;
        }
        case 7:     // 本体供电已切断
        {
            HRIF_Electrify(iBoxID_);            // 机器人上电
            break;
        }
        case 33:     // 机器人就绪
        {
            std::cout << "机器人就绪" << std::endl;
            break;
        }
        default:
        {
            break;
        }    
    }

    // 获取当前状态
    HRIF_IsMotionDone(iBoxID_, iRobotID_, RobotArmState_.bIsMotionDone_);    // 判断是否运动状态
    HRIF_IsBlendingDone(iBoxID_, iRobotID_, RobotArmState_.bIsBlendingDone_);  // 判断是否运动完成
    HRIF_ReadRobotState(iBoxID_, iRobotID_
                , RobotArmState_.iMovingState_, RobotArmState_.iEnableState_
                , RobotArmState_.iErrorState_, RobotArmState_.iErrorCode_
                , RobotArmState_.iErrorAxis_, RobotArmState_.iBreaking_
                , RobotArmState_.iPause_, RobotArmState_.iEmergencyStop_
                , RobotArmState_.iSaftyGuard_, RobotArmState_.iElectrify_
                , RobotArmState_.iIsConnectToBox_, RobotArmState_.iBlendingDone_, RobotArmState_.iInpos_);
}

bool DZ_RobotArm::Init(std::string ip, int port, int box_id, int robot_id)
{
    strIP_ = ip;
    iPort_ = port;
    iBoxID_ = box_id;
    iRobotID_ = robot_id;
    return true;
}

bool DZ_RobotArm::MoveRobotArm(std::vector<float> arr)
{
    //只能一次性传入6个数据
    if (arr.size() != 6)
    {
        cout << "数据传入错误" << endl;
        return false;
    }
    float dX = arr[0];
    float dY = arr[1];
    float dZ = arr[2];
    float dRx = arr[3];
    float dRy = arr[4];
    float dRz = arr[5];
    int nMoveType = 1;
    string sTcpName = "TCP";
    string sUcsName = "Base";
    int dVelocity = 1000;
    int dAcc = 2500;
    int dRadius = 10;
    int nIsUseJoint = 0;
    int nIsSeek = 0;
    int nIOBit = 0;
    int nIOState = 0;
    // string character;
    // character = i+'0';
    string strCmdID("0");
    
    // 定义关节命令位置
    double dJ1 = 0; double dJ2 = 0; double dJ3 = 0;
    double dJ4 = 0; double dJ5 = 0; double dJ6 = 0;
    // 读取关节命令位置
    HRIF_ReadActJointPos(iBoxID_, iRobotID_, dJ1 , dJ2 , dJ3 , dJ4 , dJ5 , dJ6);
    // 执行路点运动
    int nRetaa = HRIF_WayPoint(iBoxID_, iRobotID_, nMoveType , dX , dY , dZ , dRx , dRy , dRz 
                            , dJ1 , dJ2 , dJ3 , dJ4 , dJ5 , dJ6 
        ,sTcpName , sUcsName, dVelocity, dAcc, dRadius, nIsUseJoint, nIsSeek, nIOBit, nIOState, strCmdID);
    if (nRetaa > 0)
    {
        std::cout<< "HRIF_WayPoint 调用失败！ return -> " << nRetaa << std::endl;
    }
    return true;
}

// 机器人停止运动
bool DZ_RobotArm::GrpStop()
{
    return (HRIF_GrpStop(iBoxID_, iRobotID_) == 0);
}

// 下使能
bool DZ_RobotArm::GrpDisable()
{
    return (HRIF_GrpDisable(iBoxID_, iRobotID_) == 0);
}  

// 暂停运动
bool DZ_RobotArm::GrpInterrupt()
{
    return (HRIF_GrpInterrupt(iBoxID_, iRobotID_) == 0);
}

// 继续运动
bool DZ_RobotArm::GrpContinue()
{
    return (HRIF_GrpContinue(iBoxID_, iRobotID_) == 0);
}

bool DZ_RobotArm::RunRobotArm()
{
    WorkBase::SetSleep(100);
    WorkBase::ExecutionThread();
    return true;
}

}   // namespace COMPONENT