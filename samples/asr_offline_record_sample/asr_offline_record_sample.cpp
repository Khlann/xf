/*
* 语音听写(iFly Auto Transform)技术能够实时地将语音转换成对应的文字。
*/
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>

#include "../../include/qisr.h"
#include "../../include/msp_cmn.h"
#include "../../include/msp_errors.h"
#include "speech_recognizer.h"
#include "audio.h"
//串口唤醒相关
#include <fcntl.h>
#include <termios.h>
//时间戳
#include <time.h>
//多线程
#include <thread>
#define FRAME_LEN	640 
#define	BUFFER_SIZE	4096
#define SAMPLE_RATE_16K     (16000)
#define SAMPLE_RATE_8K      (8000)
#define MAX_GRAMMARID_LEN   (32)
#define MAX_PARAMS_LEN      (1024)

const char * ASR_RES_PATH        = "fo|res/asr/common.jet"; //离线语法识别资源路径
const char * GRM_BUILD_PATH      = "res/asr/GrmBuilld"; //构建离线语法识别网络生成数据保存路径
const char * GRM_FILE            = "call.bnf"; //构建离线识别语法网络所用的语法文件
const char * LEX_NAME            = "contact"; //更新离线识别语法的contact槽（语法文件为此示例中使用的call.bnf）

typedef struct _UserData {
	int     build_fini; //标识语法构建是否完成
	int     update_fini; //标识更新词典是否完成
	int     errcode; //记录语法构建或更新词典回调错误码
	char    grammar_id[MAX_GRAMMARID_LEN]; //保存语法构建返回的语法ID
}UserData;


const char *get_audio_file(void); //选择进行离线语法识别的语音文件
int build_grammar(UserData *udata); //构建离线识别语法网络
int update_lexicon(UserData *udata); //更新离线识别语法词典
int run_asr(UserData *udata); //进行离线语法识别

static char *g_result = NULL;
static unsigned int g_buffersize = BUFFER_SIZE;
//全局变量
short g_order=0;
int todo_id=0;
int order_id=0;
class Xunfei {
public:
	Xunfei();
	~Xunfei();
	void run();
	int Awake();
	int Stop();
	void Serial_open();
	void Serial_close();
	void Serial_read();
	void Show_result();
	void Audio_play();
private:
	//登陆信息
	const char *login_config    = "appid = 4f6310e3"; //登录参数
	UserData asr_data; 
	int ret                     = 0 ;
	char c;
	//串口数据
	int serial_fd;
	int length;
	//命令结果
	short Result;
	int Todo;
	int Order;
};


int build_grm_cb(int ecode, const char *info, void *udata)
{
	UserData *grm_data = (UserData *)udata;

	if (NULL != grm_data) {
		grm_data->build_fini = 1;
		grm_data->errcode = ecode;
	}

	if (MSP_SUCCESS == ecode && NULL != info) {
		printf("构建语法成功！ 语法ID:%s\n", info);
		if (NULL != grm_data)
			snprintf(grm_data->grammar_id, MAX_GRAMMARID_LEN - 1, info);
	}
	else
		printf("构建语法失败！%d\n", ecode);

	return 0;
}

int build_grammar(UserData *udata)
{
	FILE *grm_file                           = NULL;
	char *grm_content                        = NULL;
	unsigned int grm_cnt_len                 = 0;
	char grm_build_params[MAX_PARAMS_LEN]    = {NULL};
	int ret                                  = 0;

	grm_file = fopen(GRM_FILE, "rb");	
	if(NULL == grm_file) {
		printf("打开\"%s\"文件失败！[%s]\n", GRM_FILE, strerror(errno));
		return -1; 
	}

	fseek(grm_file, 0, SEEK_END);
	grm_cnt_len = ftell(grm_file);
	fseek(grm_file, 0, SEEK_SET);

	grm_content = (char *)malloc(grm_cnt_len + 1);
	if (NULL == grm_content)
	{
		printf("内存分配失败!\n");
		fclose(grm_file);
		grm_file = NULL;
		return -1;
	}
	fread((void*)grm_content, 1, grm_cnt_len, grm_file);
	grm_content[grm_cnt_len] = '\0';
	fclose(grm_file);
	grm_file = NULL;

	snprintf(grm_build_params, MAX_PARAMS_LEN - 1, 
		"engine_type = local, \
		asr_res_path = %s, sample_rate = %d, \
		grm_build_path = %s, ",
		ASR_RES_PATH,
		SAMPLE_RATE_16K,
		GRM_BUILD_PATH
		);
	ret = QISRBuildGrammar("bnf", grm_content, grm_cnt_len, grm_build_params, build_grm_cb, udata);

	free(grm_content);
	grm_content = NULL;

	return ret;
}

int update_lex_cb(int ecode, const char *info, void *udata)
{
	UserData *lex_data = (UserData *)udata;

	if (NULL != lex_data) {
		lex_data->update_fini = 1;
		lex_data->errcode = ecode;
	}

	if (MSP_SUCCESS == ecode)
		printf("更新词典成功！\n");
	else
		printf("更新词典失败！%d\n", ecode);

	return 0;
}

int update_lexicon(UserData *udata)
{
	const char *lex_content                   = "丁伟\n黄辣椒";
	unsigned int lex_cnt_len                  = strlen(lex_content);
	char update_lex_params[MAX_PARAMS_LEN]    = {NULL}; 

	snprintf(update_lex_params, MAX_PARAMS_LEN - 1, 
		"engine_type = local, text_encoding = UTF-8, \
		asr_res_path = %s, sample_rate = %d, \
		grm_build_path = %s, grammar_list = %s, ",
		ASR_RES_PATH,
		SAMPLE_RATE_16K,
		GRM_BUILD_PATH,
		udata->grammar_id);
	return QISRUpdateLexicon(LEX_NAME, lex_content, lex_cnt_len, update_lex_params, update_lex_cb, udata);
}


static void show_result(char *string, char is_over)
{
	printf("\rResult: [ %s ]", string);
	if(is_over)
		putchar('\n');
}


static short get_order(char *_xml_result){
  if(_xml_result == NULL){
    return 1;
  }

//get confidence
  char *str_con_first = strstr(_xml_result,"<confidence>");
  char *str_con_second = strstr(str_con_first,"</confidence"); 
  char str_confidence[4] = {'\0', '\0', '\0', '\0'};
  strncpy(str_confidence, str_con_first+12, str_con_second - str_con_first - 12);
  int confidence = atoi(str_confidence);

  if(confidence > 40){
    char *str_todo = strstr(str_con_second, "id=");
    char *str_todo_back = strstr(str_todo, ">");
    char str_todo_id[6] = {'\0', '\0', '\0', '\0', '\0', '\0'};
    strncpy(str_todo_id, str_todo+4, str_todo_back - str_todo - 5);
    todo_id = atoi(str_todo_id);
    //int order_id;

    if(todo_id < 21400){
      char *str_order = strstr(str_todo_back, "id=");
      char *str_order_back = strstr(str_order, ">");
      char str_order_id[6] = {'\0', '\0', '\0', '\0', '\0', '\0'};
      strncpy(str_order_id, str_order+4, str_order_back - str_order - 5);
      order_id = atoi(str_order_id);
    }else {
      order_id = todo_id;
    }

	time_t now = time(NULL);
	printf("结束: %ld\n", now);
	if(order_id==10002)
	{
		//play_test1();
	}
    if(order_id==10003)
	{
		//play_test2();
	}
	return order_id;
	}
}



void on_speech_begin()
{
	if (g_result)
	{
		free(g_result);
	}
	g_result = (char*)malloc(BUFFER_SIZE);
	g_buffersize = BUFFER_SIZE;
	memset(g_result, 0, g_buffersize);

	printf("Start Listening...\n");
}
void on_speech_end(int reason)
{
	if (reason == END_REASON_VAD_DETECT)
		printf("\nSpeaking done \n");
	else
		printf("\nRecognizer error %d\n", reason);
}


void on_result(const char *result, char is_last)
{
	if (result) {
		size_t left = g_buffersize - 1 - strlen(g_result);
		size_t size = strlen(result);
		if (left < size) {
			g_result = (char*)realloc(g_result, g_buffersize + BUFFER_SIZE);
			if (g_result)
				g_buffersize += BUFFER_SIZE;
			else {
				printf("mem alloc failed\n");
				return;
			}
		}
		strncat(g_result, result, size);
		//show_result(g_result, is_last);
		//printf("g_result: %s\n", g_result);
		//return (get_order(g_result));
		g_order=get_order(g_result);
		//printf("g_order: %d\n", g_order);		
	}
}

/* demo recognize the audio from microphone */
static void demo_mic(const char* session_begin_params)
{
	int errcode;
	int i = 0;

	struct speech_rec iat;

	struct speech_rec_notifier recnotifier = {
		//Xunfei::global_on_result,
		on_result,
		on_speech_begin,
		on_speech_end
	};

	errcode = sr_init(&iat, session_begin_params, SR_MIC, &recnotifier);
	if (errcode) {
		printf("speech recognizer init failed\n");
		return;
	}
	errcode = sr_start_listening(&iat);
	if (errcode) {
		printf("start listen failed %d\n", errcode);
	}
	/* demo 15 seconds recording */

	while(i++ < 15)
		sleep(1);
	errcode = sr_stop_listening(&iat);
	if (errcode) {
		printf("stop listening failed %d\n", errcode);
	}
	sr_uninit(&iat);
}

int run_asr(UserData *udata)
{	
	//离线语法识别参数设置
    char asr_params[MAX_PARAMS_LEN]    = {NULL};
	const char *rec_rslt               = NULL;
	const char *session_id             = NULL;
	const char *asr_audiof             = NULL;
	FILE *f_pcm                        = NULL;
	char *pcm_data                     = NULL;
	long pcm_count                     = 0;
	long pcm_size                      = 0;
	int last_audio                     = 0;

	int aud_stat                       = MSP_AUDIO_SAMPLE_CONTINUE;
	int ep_status                      = MSP_EP_LOOKING_FOR_SPEECH;
	int rec_status                     = MSP_REC_STATUS_INCOMPLETE;
	int rss_status                     = MSP_REC_STATUS_INCOMPLETE;
	int errcode                        = -1;
	int aud_src                        = 0;
	//离线语法识别参数设置
	snprintf
	(
		asr_params, MAX_PARAMS_LEN - 1, 
		"engine_type = local, \
		asr_res_path = %s, sample_rate = %d, \
		grm_build_path = %s, local_grammar = %s, \
		result_type = xml, result_encoding = UTF-8, ",
		ASR_RES_PATH,
		SAMPLE_RATE_16K,
		GRM_BUILD_PATH,
		udata->grammar_id
	);
    demo_mic(asr_params);
	return 0;
}



Xunfei::Xunfei()
{
	// constructor
	ret = MSPLogin(NULL, NULL, login_config); //第一个参数为用户名，第二个参数为密码，传NULL即可，第三个参数是登录参数
	if (MSP_SUCCESS != ret) {
		printf("登录失败：%d\n", ret);
		//goto exit;
		Stop();
	}
	memset(&asr_data, 0, sizeof(UserData));

	
	Serial_open();
	//return 0;	
}

Xunfei::~Xunfei()
{
	// destructor
	Stop();
	Serial_close();
}

int Xunfei::Stop()
{
	MSPLogout();
	printf("请按任意键退出...\n");
	getchar();
	return 0;
}

void Xunfei::run()
{
	if(Awake()==1)
	{
		time_t now = time(NULL);
		printf("开始: %ld\n", now);
		ret = build_grammar(&asr_data);  //第一次使用某语法进行识别，需要先构建语法网络，获取语法ID，之后使用此语法进行识别，无需再次构建
		if (MSP_SUCCESS != ret) {
			printf("构建语法调用失败！\n");
		}
		while (1 != asr_data.build_fini)////等待语法构建完成
		{
			usleep(300 * 1000);
		}	
		run_asr(&asr_data);
		Result=g_order;
		Todo=todo_id;
		Order=order_id;
		Show_result();
	}
}

void Xunfei::Serial_open()
{
	serial_fd = open("/dev/ttyUSB0", O_RDWR);
	if (serial_fd == -1) {
        perror("无法打开串口");
        exit(1);
    }
	printf("串口打开成功\n");
    struct termios options;
    tcgetattr(serial_fd, &options);
    cfsetispeed(&options, B9600);
    cfsetospeed(&options, B9600);
    options.c_cflag |= (CLOCAL | CREAD);
    options.c_cflag &= ~PARENB;
    options.c_cflag &= ~CSTOPB;
    options.c_cflag &= ~CSIZE;
    options.c_cflag |= CS8;
    tcsetattr(serial_fd, TCSANOW, &options);
}
void Xunfei::Serial_close()
{
	close(serial_fd);
}

void Xunfei::Serial_read()
{
	char buffer[255];
	length = read(serial_fd, buffer, sizeof(buffer));
	//printf("Buffer: %s\n", buffer);
	printf("字节数%d\n",length);
}

int Xunfei::Awake()
{
	//串口唤醒
	printf("等待语音唤醒\n");
	Serial_read();
	if(length>10)
	{
		printf("唤醒成功\n");
		Serial_close();
		return 1;
	}
	else
	{
		printf("等待语音唤醒\n");
		return 0;
	}
}

void Xunfei::Show_result()
{
	printf("Result:%d\n",Result);
	printf("Todo:%d\n",Todo);
	printf("Order:%d\n",Order);
}

void Xunfei::Audio_play()
{
	if(Order==10002)
	{
		//play_test1();
	}
	if(Order==10003)
	{
		//play_test2();
	}
}
int main(int argc, char* argv[])
{
    Xunfei xunfei;
    // Create a thread for the run function
    std::thread runThread(&Xunfei::run, &xunfei);
    runThread.join();
    return 0;
}


