#include "LLog/LLog.h"
#include <iostream>
#include <sys/stat.h>
#include <ctime>
#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>

namespace LLOG {

LLog::LLog(TLogLevel log_level, std::string module_name, std::string folder_name, int file_size)
    :  strModuleName_(module_name), strFolderName_(folder_name), nFileSize_(file_size*1024)
{
    eLogLevel_ = log_level;
    bStop_ = true;
    InitLog();
    mapLevelName.insert(std::make_pair<TLogLevel, std::string>((TLogLevel)TLogLevel::STOP, (std::string)STOP_PREFIX));
    mapLevelName.insert(std::make_pair<TLogLevel, std::string>((TLogLevel)TLogLevel::FATAL, (std::string)FATAL_PREFIX));
    mapLevelName.insert(std::make_pair<TLogLevel, std::string>((TLogLevel)TLogLevel::ERROR, (std::string)ERROR_PREFIX));
    mapLevelName.insert(std::make_pair<TLogLevel, std::string>((TLogLevel)TLogLevel::WARNING, (std::string)WARNING_PREFIX));
    mapLevelName.insert(std::make_pair<TLogLevel, std::string>((TLogLevel)TLogLevel::DEBUG, (std::string)DEBUG_PREFIX));
    StartThread();
}


LLog::~LLog()
{
    StopThread();
}


void LLog::InitLog()
{
    //创建目录
    if (strFolderName_[strFolderName_.size()-1] != '/')
    {
        strFolderName_ += "/";
    }
    mkdir(strFolderName_.c_str(), 0777);
    //创建模块路径
    std::string strTemp = strFolderName_ + strModuleName_;
    if (strModuleName_[strModuleName_.size()-1] != '/')
    {
        strTemp += "/";
    }
    mkdir(strTemp.c_str(), 0777);
    //创建时间目录
    time_t t = time(NULL); 
    char buf[64] = {0};
    strftime(buf, sizeof(buf)-1, "%Y_%m_%d", localtime(&t)); 
    strTemp += buf;
    mkdir(strTemp.c_str(), 0777);
    strFolderTime_ = buf;
}


void LLog::StartThread()
{
    bStop_ = false;
    threadFd_ = std::thread(&LLog::Proc, this);
}


void LLog::StopThread()
{
    bStop_ = true;
    conditionThread_.notify_one();
    threadFd_.join();
}


void LLog::SetFileSize(int file_size)
{
    nFileSize_ = file_size * 1024;
}


void LLog::SetFolderName(std::string folder_name)
{
    strFolderName_ = folder_name;
}


void LLog::SetModuleName(std::string module_name)
{
    strModuleName_ = module_name;
}


void LLog::SetLogLevel(TLogLevel log_level)
{
    eLogLevel_ = log_level;
}


bool LLog::AddLog(int line, std::string file_name, char const *data, int data_size, TLogLevel level)
{
    if (data == NULL)
    {
        return false;
    }
    Task *pTask = new Task();
    if (pTask == NULL)
    {
        return false;
    }
    pTask->pData = new char[data_size];
    if (pTask->pData == NULL)
    {
        delete pTask;
        return false;
    }
    memcpy(pTask->pData, data, data_size);
    pTask->nDataSize = data_size;
    pTask->nLine = line;
    pTask->strFileName = file_name;
    pTask->eLogLevel = level;

    queueTask_.push(pTask);         //插入队列
    conditionThread_.notify_one();  //唤醒线程
    return true;
}


void LLog::Proc()
{
    while(1)
    {
        Task *pTask = NULL;
        if (queueTask_.empty()) //判断队列是不是为空
        {
            std::unique_lock<std::mutex> lock(mutexThread_);
            conditionThread_.wait(lock);    //休眠
            if (bStop_ && (queueTask_.empty())) //退出
            {
                return;
            }
        }
        //取出数据
        pTask = queueTask_.front();
        queueTask_.pop();
        if (pTask->eLogLevel > eLogLevel_)
        {
            delete []pTask->pData;
            delete pTask;
            continue;
        }
        //生成年月日时间信息
        std::time_t tTime;
	    std::tm* pTime = Gettm(tTime);   
        char szTime[64] = {0};
        sprintf(szTime, "%04d_%02d_%02d", pTime->tm_year+1900, pTime->tm_mon+1, pTime->tm_mday);
        if (strFolderTime_.compare(szTime) != 0)
        {
            InitLog();
            strLogName_ = "";
//            std::cout<< __LINE__ <<std::endl;
        }
        int nFileSize = GetFileSize(strLogName_);
        //std::cout<< nFileSize <<std::endl;
        if (nFileSize == -1 || nFileSize+pTask->nDataSize > nFileSize_)
        {
            strLogName_ = strFolderName_ + strModuleName_;
            memset(szTime, 0, 64);
            sprintf(szTime, "%02d_%02d_%02d", pTime->tm_hour, pTime->tm_min, pTime->tm_sec);
            strLogName_ += "/" + strFolderTime_ + "/";
            strLogName_ += szTime;
//            std::cout<< "strLogName:" << strLogName_ << "  nFileSize:" << nFileSize
//                << "  DataSize" << nFileSize+pTask->nDataSize <<std::endl;
        }
        memset(szTime, 0, 64);
        sprintf(szTime, "%4d-%02d-%02d %02d:%02d:%02d.%ld"
            , pTime->tm_year+1900, pTime->tm_mon+1, pTime->tm_mday, pTime->tm_hour, pTime->tm_min, pTime->tm_sec, tTime%1000);

        int nLogLen = strlen(szTime) + pTask->strFileName.size() + 20; //日志行数值长度 + [][][] 预计是20个字节
        char *pData = new char[nLogLen];
        memset(pData, 0, nLogLen);
        sprintf(pData, "%s [%s][%d][%s]\t", szTime, pTask->strFileName.c_str(), pTask->nLine, mapLevelName[pTask->eLogLevel].c_str());

        //写入文件中
        int file_fd = open(strLogName_.c_str(), O_WRONLY|O_APPEND|O_CREAT, S_IRUSR|S_IWUSR|S_IXUSR|S_IRGRP|S_IWGRP|S_IROTH);
        if(file_fd == -1)
        {
            std::cout<< "file_fd" << file_fd <<std::endl;
        }
        ssize_t w_size = write(file_fd, pData, (size_t)strlen(pData));      //日志信息
        w_size = write(file_fd, pTask->pData, (size_t)pTask->nDataSize);    //日志内容
        w_size = write(file_fd, "\n", 1);   //换行
        (void)w_size;
        close(file_fd);
        delete []pData;
        delete []pTask->pData;
        delete pTask;
    }
}


int LLog::GetFileSize(std::string &file_path)
{
    struct stat statbuf;
    if(stat(file_path.c_str(), &statbuf) == 0)
        return statbuf.st_size;
    return -1;
}


std::tm* LLog::Gettm(std::time_t &milli)
{
    std::chrono::time_point<std::chrono::system_clock,std::chrono::milliseconds> tp = std::chrono::time_point_cast<std::chrono::milliseconds>(std::chrono::system_clock::now());
    auto tmp=std::chrono::duration_cast<std::chrono::milliseconds>(tp.time_since_epoch());
    milli = tmp.count() + (std::time_t)8*60*60*1000;
    auto mTime = std::chrono::milliseconds(milli);
    auto tp1=std::chrono::time_point<std::chrono::system_clock,std::chrono::milliseconds>(mTime);
    auto tt = std::chrono::system_clock::to_time_t(tp1);
    std::tm *now = std::gmtime(&tt);
    return now;
}

}   // namespace LLOG
