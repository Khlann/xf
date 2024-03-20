#ifndef XIAOHAI_ROBOT_H
#define XIAOHAI_ROBOT_H
#include "work_base.h"
#include "central_server_tcp.h"
#include <queue>

namespace ROBOTS {

class XiaoHaiRobot : public COMMON::WorkBase
{
public:
    XiaoHaiRobot();
    ~XiaoHaiRobot();

    void Init();
    void CentralServerCallBack(const nlohmann::json& json_data);
    void WorkFun();
    // virtual bool TaskScheduler(nlohmann::json &task_data);   // 任务调度
public:
    COMMON::CentralServerTcp CentralServer_;
    std::queue<nlohmann::json> quQueryTasks_;// 机器人 查询任务
    std::queue<nlohmann::json> quProcessTasks_;// 机器人 流程任务
};


}    // namespace ROBOTS
#endif