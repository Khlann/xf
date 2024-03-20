#ifndef LLOG_H
#define LLOG_H

#include <string.h>
#include <queue>
#include <vector>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <functional>
#include <map>


namespace LLOG {

#define FILE_MAX_SIZE 200   //单个日志文件最大大小M为单位
#define FOLDER_PATH   "./LLOG"      //日志文件目录
#define STOP_PREFIX    "Stop"
#define FATAL_PREFIX    "Fatal"
#define ERROR_PREFIX    "Error"
#define WARNING_PREFIX  "Warning"
#define DEBUG_PREFIX    "Debug"

//优先级
typedef enum _LogLevel {
    STOP = 0,       //什么都不显示
    FATAL,          //严重
    ERROR,          //错误
    WARNING,        //告警
    DEBUG           //调试级别
    
}TLogLevel;


class Task{

public:
    Task()
    {}
    ~Task()
    {}

public:
    int nDataSize;
    char *pData;            //任务数据
    TLogLevel eLogLevel;    //日志级别
    int nLine;              //行号
    std::string strFileName;    //代码文件名
};

class LLog{

public:
    LLog(TLogLevel log_level, std::string module_name, std::string folder_name = FOLDER_PATH, int file_size = FILE_MAX_SIZE);
    ~LLog();
    void SetFileSize(int file_size);
    void SetFolderName(std::string folder_name);
    void SetModuleName(std::string module_name);
    void SetLogLevel(TLogLevel log_level);
    bool AddLog(int line, std::string file_name, char const *data, int data_size, TLogLevel level);
    void StopThread();

public:
    void InitLog();
    void StartThread();
    void Proc();
    int GetFileSize(std::string &file_path);
    std::tm* Gettm(std::time_t &milli);
private:
    bool        bStop_;             //停止并退出线程
    std::string strModuleName_;     //模块名称
    std::string strFolderName_;     //文件夹名称
    std::string strFolderTime_;     //文件夹时间
    std::string strLogName_;        //记录日志需要存入的路径
    int         nFileSize_;         //文件大小
    TLogLevel   eLogLevel_;         //日志级别
    std::queue<Task*> queueTask_;   //任务队列
    std::thread threadFd_;          //写磁盘文件线程
    std::mutex mutexThread_;        //线程锁
    std::condition_variable conditionThread_;    //线程条件变量
    std::map<TLogLevel, std::string> mapLevelName; //级别名称
};

}   // namespace LLOG

#endif // LLOG_H
