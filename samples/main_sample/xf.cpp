#include "xf.h"
#include <c++/7/iomanip>
#include <iomanip>

const char * ASR_RES_PATH        = "fo|res/asr/common.jet"; //离线语法识别资源路径
const char * GRM_BUILD_PATH      = "res/asr/GrmBuilld"; //构建离线语法识别网络生成数据保存路径
const char * GRM_FILE            = "call.bnf"; //构建离线识别语法网络所用的语法文件
const char * LEX_NAME            = "contact"; //更新离线识别语法的contact槽（语法文件为此示例中使用的call.bnf）
static char *g_result = NULL;
static unsigned int g_buffersize = BUFFER_SIZE;
//全局变量
short g_order=0;
int want_id=0;
int dialpre_id=0;
int contact_id=0;
int todo_id=0;
int order_id=0;
/* 默认wav音频头部数据 */
wave_pcm_hdr default_wav_hdr = 
{
	{ 'R', 'I', 'F', 'F' },
	0,
	{'W', 'A', 'V', 'E'},
	{'f', 'm', 't', ' '},
	16,
	1,
	1,
	16000,
	32000,
	2,
	16,
	{'d', 'a', 't', 'a'},
	0  
};

XF::XF()
{
	// constructor
    const char *login_config    = "appid = 4f6310e3"; //登录参数
    //UserData asr_data; 
	int ret = MSPLogin(NULL, NULL, login_config); //第一个参数为用户名，第二个参数为密码，传NULL即可，第三个参数是登录参数
	if (MSP_SUCCESS != ret) {
		printf("登录失败：%d\n", ret);
		//goto exit;
		Stop();
	}
	memset(&asr_data, 0, sizeof(UserData));
    cout<<"开始打开串口"<<endl;
    if(Serial_open())
    {
        cout<<"打开串口成功"<<endl;
    }
    else
    {
        cout<<"打开串口失败"<<endl;
    }
}

XF::~XF()
{
    // destructor

}

bool XF::Serial_open()
{
	serial_fd = open("/dev/ttyUSB0", O_RDWR);
	if (serial_fd == -1) {
        return false;
    }
    struct termios options;
    tcgetattr(serial_fd, &options);
    cfsetispeed(&options, B115200);
    cfsetospeed(&options, B115200);
    options.c_cflag |= (CLOCAL | CREAD);
    options.c_cflag &= ~PARENB;
    options.c_cflag &= ~CSTOPB;
    options.c_cflag &= ~CSIZE;
    options.c_cflag |= CS8;
    tcsetattr(serial_fd, TCSANOW, &options);
    return true;
}

int XF::Stop()
{
	MSPLogout();
	printf("请按任意键退出...\n");
	getchar();
	return 0;
}

bool XF::Awake()
{
    if(Receive_woshou()==true)
    {
        cout<<"握手成功,等待唤醒"<<endl;
        Sent_conformation();	
        Receive_dynamic_data();
        return true;
    }
    else
    {
        cout<<"握手失败"<<endl;
        return false;
    }
}

bool XF::Receive_woshou()
{
    const vector<unsigned char> HEAD={0xa5,0x01};
    const unsigned char TAIL=0xb0;
    const size_t HANDSHAKE_LENGTH = 11; // 帧头 + 9个字节 + 帧尾
    deque<unsigned char> buffer;
    unsigned char byte;

    while(true)
    {
        if(read(serial_fd, &byte, 1))
        {
            buffer.push_back(byte);
            if(buffer.size()>HEAD.size())
            {
                if(!equal(HEAD.begin(),HEAD.end(),buffer.begin()))
                {
                    buffer.pop_front();
                }
            }
            if(buffer.size()==HANDSHAKE_LENGTH)
            {
                if(buffer.back()==TAIL)
                {

                    return true;
                }
                else
                {
                    buffer.clear();
                }
            }

        }
    }
}

bool XF::Sent_conformation()
{
    const vector<unsigned char> CONFORM={
        0xa5,0x01,//帧头
        0xff,0x04,0x00,0x00,0x00,0xa5,0x00,0x00,0x00,//数据
        0xb2//帧尾
    };
    ssize_t n=write(serial_fd,CONFORM.data(),CONFORM.size());

    return n==static_cast<ssize_t>(CONFORM.size());
}

bool XF::Receive_dynamic_data()
{
    const vector<unsigned char> HEAD={0x7b,0x22,0x63,0x6f,0x6e};//帧头
    const vector<unsigned char> TAIL={0x65,0x6e,0x74,0x22,0x7d};//帧尾
    //vector<unsigned char> header(7);//帧头+数据长度字段+消息ID
    deque<unsigned char> buffer;
    unsigned char byte;

    // if(!read(serial_fd,header.data(),header.size()))
    // {
    //     return false;
    // }
    while(true)
    {
        if(read(serial_fd,&byte,1))
        {

            //下面4行代码用于调试，可以删除
            // cout<<"buffer.size():"<<buffer.size()<<"原始byte"<<byte<<"字节为："<<
            // std::hex << std::setw(2) << std::setfill('0') << static_cast<int>(static_cast<unsigned char>(byte) );
            // buffer.push_back(byte);
            // std::cout << "begin"<<hex << std::setw(2) << std::setfill('0') << static_cast<int>(static_cast<unsigned char>(buffer[buffer.size()-1]) )<<endl;
            buffer.push_back(byte);
            if(buffer.size()>HEAD.size())
            {
                if(!(buffer[0]==HEAD[0]&&buffer[1]==HEAD[1])&&buffer[2]==HEAD[2]&&buffer[3]==HEAD[3]&&buffer[4]==HEAD[4])
                {
                   // cout<<"帧头错误"<<endl;
                    buffer.pop_front();
                }
            }
            if(buffer[buffer.size()-1]==TAIL[4]&&buffer[buffer.size()-2]==TAIL[3]&&buffer[buffer.size()-3]==TAIL[2]&&buffer[buffer.size()-4]==TAIL[1]&&buffer[buffer.size()-5]==TAIL[0])
            {
                //cout<<"帧尾正确"<<endl;
                return true;
            }
            // if(buffer.size()==4)//大小端问题
            // {
            //    length=static_cast<uint16_t>(buffer[3])|(static_cast<uint16_t>(buffer[4])<<8);
            //   // cout<<"length:"<<length<<endl;
              
            // }
        }
    }


}

int XF::build_grammar(UserData *udata)
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

void XF::Run()
{
    if(Awake()==1)
	{
		time_t now = time(NULL);
		cout<<"唤醒成功"<<endl;
		cout<<"语音识别开始时间:"<<now<<endl;
		int ret = build_grammar(&asr_data);  //第一次使用某语法进行识别，需要先构建语法网络，获取语法ID，之后使用此语法进行识别，无需再次构建
		if (MSP_SUCCESS != ret) {
			cout<<"构建语法调用失败！"<<endl;
		}
		while (1 != asr_data.build_fini)////等待语法构建完成
		{
			usleep(300 * 1000);
		}	
		run_asr(&asr_data);
		Result=g_order;
		Show_result();
	}
}

void XF::Show_result()
{
    cout<<"结果："<<"Todo_id:"<<todo_id<<" Want_id:"<<order_id<<endl;
}

int XF::run_asr(UserData *udata)
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
void XF::demo_mic(const char* session_begin_params)
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

string XF::User_tts()
{
	const char* session_begin_params = "engine_type = local,voice_name=xiaoyan, text_encoding = UTF8, tts_res_path = fo|res/tts/xiaoyan.jet;fo|res/tts/common.jet, sample_rate = 16000, speed = 50, volume = 50, pitch = 50, rdn = 2";
	string filename;
	string text;
	cout << "请输入合成的语音文件名称,请以.wav结束" << endl;
	getline(cin, filename);

	cout << "请输入合成文本" << endl;
	getline(cin, text);

	text_to_speech(text.c_str(), filename.c_str(), session_begin_params);
	return filename;
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
		show_result(g_result, is_last);//显示结果
		//printf("g_result: %s\n", g_result);
		//return (get_order(g_result));
		g_order=get_order(g_result);
		//printf("g_order: %d\n", g_order);		
	}
}

static short get_order(char *_xml_result)
{
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

    // char *str_todo = strstr(str_con_second, "id=");
    // char *str_todo_back = strstr(str_todo, ">");
	// char *str_order = strstr(str_todo_back, "id=");
	// char *str_order_back = strstr(str_order, ">");
	// //char *str_contact = strstr(str_order_back, "id=");
	// //char *str_contact_back = strstr(str_contact, ">");
    // char str_todo_id[6] = {'\0', '\0', '\0', '\0', '\0', '\0'};
	// char str_order_id[6] = {'\0', '\0', '\0', '\0', '\0', '\0'};
	// char str_contact_id[6] = {'\0', '\0', '\0', '\0', '\0', '\0'};
    // strncpy(str_todo_id, str_todo+4, str_todo_back - str_todo - 5);
	// strncpy(str_order_id, str_order+4, str_order_back - str_order - 5);
	// //strncpy(str_contact_id, str_contact+4, str_contact_back - str_contact - 5);
    // want_id = atoi(str_todo_id);
	// dialpre_id = atoi(str_order_id);
	// //contact_id = atoi(str_contact_id);

	time_t now = time(NULL);
	cout<<"语音识别结束时间:"<<now<<endl;
	return 1;
	}
}

static void show_result(char *string, char is_over)
{
	printf("\rResult: [ %s ]", string);
	if(is_over)
		putchar('\n');
}

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

int XF::text_to_speech(const char* src_text, const char* des_path, const char* params)
{
	int          ret          = -1;
	FILE*        fp           = NULL;
	const char*  sessionID    = NULL;
	unsigned int audio_len    = 0;
	wave_pcm_hdr wav_hdr      = default_wav_hdr;
	int          synth_status = MSP_TTS_FLAG_STILL_HAVE_DATA;

	if (NULL == src_text || NULL == des_path)
	{
		printf("params is error!\n");
		return ret;
	}
	fp = fopen(des_path, "wb");
	if (NULL == fp)
	{
		printf("open %s error.\n", des_path);
		return ret;
	}
	/* 开始合成 */
	sessionID = QTTSSessionBegin(params, &ret);
	if (MSP_SUCCESS != ret)
	{
		printf("QTTSSessionBegin failed, error code: %d.\n", ret);
		fclose(fp);
		return ret;
	}
	ret = QTTSTextPut(sessionID, src_text, (unsigned int)strlen(src_text), NULL);
	if (MSP_SUCCESS != ret)
	{
		printf("QTTSTextPut failed, error code: %d.\n",ret);
		QTTSSessionEnd(sessionID, "TextPutError");
		fclose(fp);
		return ret;
	}
	printf("正在合成 ...\n");
	fwrite(&wav_hdr, sizeof(wav_hdr) ,1, fp); //添加wav音频头，使用采样率为16000
	while (1) 
	{
		/* 获取合成音频 */
		const void* data = QTTSAudioGet(sessionID, &audio_len, &synth_status, &ret);
		if (MSP_SUCCESS != ret)
			break;
		if (NULL != data)
		{
			fwrite(data, audio_len, 1, fp);
		    wav_hdr.data_size += audio_len; //计算data_size大小
		}
		if (MSP_TTS_FLAG_DATA_END == synth_status)
			break;
	}
	printf("\n");
	if (MSP_SUCCESS != ret)
	{
		printf("QTTSAudioGet failed, error code: %d.\n",ret);
		QTTSSessionEnd(sessionID, "AudioGetError");
		fclose(fp);
		return ret;
	}
	/* 修正wav文件头数据的大小 */
	wav_hdr.size_8 += wav_hdr.data_size + (sizeof(wav_hdr) - 8);
	
	/* 将修正过的数据写回文件头部,音频文件为wav格式 */
	fseek(fp, 4, 0);
	fwrite(&wav_hdr.size_8,sizeof(wav_hdr.size_8), 1, fp); //写入size_8的值
	fseek(fp, 40, 0); //将文件指针偏移到存储data_size值的位置
	fwrite(&wav_hdr.data_size,sizeof(wav_hdr.data_size), 1, fp); //写入data_size的值
	fclose(fp);
	fp = NULL;
	/* 合成完毕 */
	ret = QTTSSessionEnd(sessionID, "Normal");
	if (MSP_SUCCESS != ret)
	{
		printf("QTTSSessionEnd failed, error code: %d.\n",ret);
	}

	return ret;
}

int XF::Audio_play(string str)
{
    if (SDL_Init(SDL_INIT_AUDIO) < 0) {
        SDL_Log("Unable to initialize SDL: %s", SDL_GetError());
        return 1;
    }
    const char* cstr = str.c_str();
    SDL_AudioSpec wavSpec;
    Uint32 wavLength;
    Uint8 *wavBuffer;

    if (SDL_LoadWAV(cstr, &wavSpec, &wavBuffer, &wavLength) == NULL) {
        SDL_Log("Unable to load wav file: %s", SDL_GetError());
        return 1;
    }
    
    SDL_AudioDeviceID deviceId = SDL_OpenAudioDevice(NULL, 0, &wavSpec, NULL, 0);
    if (deviceId == 0) {
        SDL_Log("Failed to open audio device: %s", SDL_GetError());
        return 1;
    }

    if (SDL_QueueAudio(deviceId, wavBuffer, wavLength) < 0) {
        SDL_Log("Failed to queue audio: %s", SDL_GetError());
        return 1;
    }
    SDL_PauseAudioDevice(deviceId, 0);

    // 等待音频播放完成
    while (SDL_GetQueuedAudioSize(deviceId) > 0) {
        SDL_Delay(100);
    }

    SDL_CloseAudioDevice(deviceId);
    SDL_FreeWAV(wavBuffer);
    SDL_Quit();

    return 0;
}