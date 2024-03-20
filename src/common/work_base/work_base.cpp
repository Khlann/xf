#include "work_base.h"
#include <iostream>

namespace COMMON{

WorkBase::WorkBase(WhileType type)
{
    bIsStop_ = false;
    WhileType_ = type;
    iSleepTime_ = 5000;

    if (WhileType_ == WhileType::SEMAPHORE)
    {
        sem_init(&semWork_, 0, 0);
    }
}

WorkBase::~WorkBase()
{
    if (WhileType_ == WhileType::SEMAPHORE)
    {
        std::cout << "~WorkBase SEMAPHORE s" << std::endl;
    }
    else
    {
        std::cout << "~WorkBase TIME s" << std::endl;
    }
    Stop();
    if (thWorkThread_.joinable())
    {
        thWorkThread_.join();
    }
    sem_destroy(&semWork_);
    if (WhileType_ == WhileType::SEMAPHORE)
    {
        std::cout << "~WorkBase SEMAPHORE e" << std::endl;
    }
    else
    {
        std::cout << "~WorkBase TIME e" << std::endl;
    }
}

bool WorkBase::ExecutionThread()
{
    if (thWorkThread_.joinable())
    {
        return true;
    }
    thWorkThread_ = std::thread(&WorkBase::ThreadFun, this);
    if (!thWorkThread_.joinable())
    {
        return false;
    }
    return true;
}

void WorkBase::SemaphoreActivation()
{
    if (WhileType_ == WhileType::SEMAPHORE)
    {
        sem_post(&semWork_);
    }
}

void WorkBase::SetSleep(int time)
{
    iSleepTime_ = time;
}

void WorkBase::ThreadFun()
{
    while(!bIsStop_)
    {
        if (WhileType_ == WhileType::SEMAPHORE)
        {
            sem_wait(&semWork_);
            if (bIsStop_)
            {
                break;
            }
        }

        WorkFun();

        if (WhileType_ == WhileType::TIME)
        {
            std::this_thread::sleep_for(std::chrono::milliseconds(iSleepTime_));
        }
    }
}

void WorkBase::Stop()
{
    bIsStop_ = true;
    if (WhileType_ == WhileType::SEMAPHORE)
    {
        sem_post(&semWork_);
    }
}

void WorkBase::WorkFun()
{
}

}
