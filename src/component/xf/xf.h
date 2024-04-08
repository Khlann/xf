// C 标准库头文件
#include <stdio.h>      // 提供了一系列输入和输出功能
#include <stdlib.h>     // 提供了一系列内存管理、随机数生成、通信等功能
#include <string.h>     // 提供了一系列字符串操作功能
#include <errno.h>      // 提供了通过错误码报告错误的功能
#include <time.h>       // 提供了时间和日期的操作功能

// Unix/Linux 系统头文件
#include <unistd.h>     // 提供了一系列 Unix/Linux 系统调用功能
#include <fcntl.h>      // 提供了文件控制功能
#include <termios.h>    // 提供了终端 I/O 功能

// C++ 标准库头文件
#include <iostream>     // 提供了一系列输入和输出功能
#include <vector>       // 提供了动态数组功能
#include <deque>        // 提供了双端队列功能
#include <fstream>      // 提供了文件输入和输出功能
#include <thread>       // 提供了多线程功能

// 第三方库头文件
#include <nlohmann/json.hpp>  // 提供了 JSON 操作功能

// 项目内部头文件
#include "qisr.h"           // 语音识别功能
#include "msp_cmn.h"        // 语音识别功能
#include "msp_errors.h"     // 错误处理功能
#include "speech_recognizer.h"            // 语音识别功能
#include "qtts.h"
#include <SDL2/SDL.h>
#include "/usr/include/SDL2/SDL.h"
//#include "audio.h"                        // 音频处理功能

using namespace std;

#define FRAME_LEN	640 
#define	BUFFER_SIZE	4096
#define SAMPLE_RATE_16K     (16000)
#define SAMPLE_RATE_8K      (8000)
#define MAX_GRAMMARID_LEN   (32)
#define MAX_PARAMS_LEN      (1024)



typedef struct _UserData {
	int     build_fini; //标识语法构建是否完成
	int     update_fini; //标识更新词典是否完成
	int     errcode; //记录语法构建或更新词典回调错误码
	char    grammar_id[MAX_GRAMMARID_LEN]; //保存语法构建返回的语法ID
}UserData;

/* 文本合成 */
typedef int SR_DWORD;
typedef short int SR_WORD ;

#define AUDIO_FILE_PATH "test1.wav"

/* wav音频头部格式 */
typedef struct _wave_pcm_hdr
{
	char            riff[4];                // = "RIFF"
	int				size_8;                 // = FileSize - 8
	char            wave[4];                // = "WAVE"
	char            fmt[4];                 // = "fmt "
	int				fmt_size;				// = 下一个结构体的大小 : 16

	short int       format_tag;             // = PCM : 1
	short int       channels;               // = 通道数 : 1
	int				samples_per_sec;        // = 采样率 : 8000 | 6000 | 11025 | 16000
	int				avg_bytes_per_sec;      // = 每秒字节数 : samples_per_sec * bits_per_sample / 8
	short int       block_align;            // = 每采样点字节数 : wBitsPerSample / 8
	short int       bits_per_sample;        // = 量化比特数: 8 | 16

	char            data[4];                // = "data";
	int				data_size;              // = 纯数据长度 : FileSize - 44 
} wave_pcm_hdr;

int text_to_speech(const char* src_text, const char* des_path, const char* params);
int play_test1();

void on_speech_begin();
void on_speech_end(int reason);
void on_result(const char *result, char is_last);
static short get_order(char *_xml_result);
static void show_result(char *string, char is_over);
int build_grm_cb(int ecode, const char *info, void *udata);
class XF
{
    public:
        UserData asr_data; // 语音识别数据
    	XF();
        ~XF();

        /**
         * @brief 用于唤醒
         * 
         * @return 
         *     - true: 唤醒成功
         *    - false: 唤醒失败
         */
        bool Awake();
        /**
         * @brief 用于打开串口
         * 
         * @return 
         *     - true: 打开成功
         *    - false: 打开失败
         */
        bool Serial_open();

        /**
         * @brief 用于接收握手信息
         * 
         * @return 
         *     - true: 接收成功
         *    - false: 接收失败
         */
        bool Receive_woshou();
        /**
         * @brief 用于发送握手确认信息
         * 
         * @return 
         *     - true: 发送成功
         *    - false: 发送失败
         */
        bool Sent_conformation();
        /**
         * @brief 用于接收动态串口数据
         * 
         *       这里需要定义帧头和帧尾，用于判断是否接收到完整的数据
         * 
         * @return 
         *     - true: 接收到完整的数据
         *    - false: 未接收到完整的数据
         */
        bool Receive_dynamic_data();
        /**
         * @brief 命令词识别
         * 
         **/
        void Run();
        int build_grammar(UserData *udata);
        int run_asr(UserData *udata);
        void demo_mic(const char* session_begin_params);
        void Show_result();
        /**
         * @brief 用于合成语音
         * 
         * @return 
         *     - true: 合成成功
         *    - false: 合成失败
         */
        int text_to_speech(const char* src_text, const char* des_path, const char* params);
        /**
         * @brief 用户用于合成语音
         * 
         * @return 
         *     - true: 合成成功
         *    - false: 合成失败
         */
        string User_tts();
        /**
         * @brief 用于播放语音
         * 
         * @return 
         *     - true: 播放成功
         *    - false: 播放失败
         */
        int Audio_play(string str);


    private:
        //串口数据
        int serial_fd;
        int length;
        int buf_flag=1;   //标志位，用于判断是否接收到数据
        int index=0;
        std::vector<int> my_vector;
        std::vector<int> data_list;
        int Stop();

        short Result;
        int Todo;
        int Order;

        int want_id;
        int dialpre_id;
        int contact_id;
};