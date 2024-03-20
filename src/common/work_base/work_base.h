#ifndef WORKBASE_H
#define WORKBASE_H
#include <thread>
#include <semaphore.h>

namespace COMMON{

enum WhileType
{
    TIME = 0,
    SEMAPHORE
};

class WorkBase
{
public:
    WorkBase(WhileType type);
    virtual ~WorkBase();
    bool ExecutionThread();
    void SetSleep(int time);
    void SemaphoreActivation();
    virtual void WorkFun();
    void Stop();
private:
    void ThreadFun();

private:
    std::thread thWorkThread_;
    WhileType WhileType_;
    bool bIsStop_;
    int iSleepTime_;
    sem_t semWork_;
};


}
#endif // WORKBASE_H
