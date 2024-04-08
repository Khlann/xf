
// /*
// * 语音合成（Text To Speech，TTS）技术能够自动将任意文字实时转换为连续的
// * 自然语音，是一种能够在任何时间、任何地点，向任何人提供语音信息服务的
// * 高效便捷手段，非常符合信息时代海量数据、动态更新和个性化查询的需求。
// */

// #include <stdlib.h>
// #include <stdio.h>
// #include <unistd.h>
// #include <errno.h>
// #include "../../include/qtts.h"
// #include "../../include/msp_cmn.h"
// #include "../../include/msp_errors.h"
// #include <SDL2/SDL.h>
// #include "audio.h"

// /* 默认wav音频头部数据 */
// wave_pcm_hdr default_wav_hdr = 
// {
// 	{ 'R', 'I', 'F', 'F' },
// 	0,
// 	{'W', 'A', 'V', 'E'},
// 	{'f', 'm', 't', ' '},
// 	16,
// 	1,
// 	1,
// 	16000,
// 	32000,
// 	2,
// 	16,
// 	{'d', 'a', 't', 'a'},
// 	0  
// };
// int text_to_speech(const char* src_text, const char* des_path, const char* params)
// {
// 	int          ret          = -1;
// 	FILE*        fp           = NULL;
// 	const char*  sessionID    = NULL;
// 	unsigned int audio_len    = 0;
// 	wave_pcm_hdr wav_hdr      = default_wav_hdr;
// 	int          synth_status = MSP_TTS_FLAG_STILL_HAVE_DATA;

// 	if (NULL == src_text || NULL == des_path)
// 	{
// 		printf("params is error!\n");
// 		return ret;
// 	}
// 	fp = fopen(des_path, "wb");
// 	if (NULL == fp)
// 	{
// 		printf("open %s error.\n", des_path);
// 		return ret;
// 	}
// 	/* 开始合成 */
// 	sessionID = QTTSSessionBegin(params, &ret);
// 	if (MSP_SUCCESS != ret)
// 	{
// 		printf("QTTSSessionBegin failed, error code: %d.\n", ret);
// 		fclose(fp);
// 		return ret;
// 	}
// 	ret = QTTSTextPut(sessionID, src_text, (unsigned int)strlen(src_text), NULL);
// 	if (MSP_SUCCESS != ret)
// 	{
// 		printf("QTTSTextPut failed, error code: %d.\n",ret);
// 		QTTSSessionEnd(sessionID, "TextPutError");
// 		fclose(fp);
// 		return ret;
// 	}
// 	printf("正在合成 ...\n");
// 	fwrite(&wav_hdr, sizeof(wav_hdr) ,1, fp); //添加wav音频头，使用采样率为16000
// 	while (1) 
// 	{
// 		/* 获取合成音频 */
// 		const void* data = QTTSAudioGet(sessionID, &audio_len, &synth_status, &ret);
// 		if (MSP_SUCCESS != ret)
// 			break;
// 		if (NULL != data)
// 		{
// 			fwrite(data, audio_len, 1, fp);
// 		    wav_hdr.data_size += audio_len; //计算data_size大小
// 		}
// 		if (MSP_TTS_FLAG_DATA_END == synth_status)
// 			break;
// 	}
// 	printf("\n");
// 	if (MSP_SUCCESS != ret)
// 	{
// 		printf("QTTSAudioGet failed, error code: %d.\n",ret);
// 		QTTSSessionEnd(sessionID, "AudioGetError");
// 		fclose(fp);
// 		return ret;
// 	}
// 	/* 修正wav文件头数据的大小 */
// 	wav_hdr.size_8 += wav_hdr.data_size + (sizeof(wav_hdr) - 8);
	
// 	/* 将修正过的数据写回文件头部,音频文件为wav格式 */
// 	fseek(fp, 4, 0);
// 	fwrite(&wav_hdr.size_8,sizeof(wav_hdr.size_8), 1, fp); //写入size_8的值
// 	fseek(fp, 40, 0); //将文件指针偏移到存储data_size值的位置
// 	fwrite(&wav_hdr.data_size,sizeof(wav_hdr.data_size), 1, fp); //写入data_size的值
// 	fclose(fp);
// 	fp = NULL;
// 	/* 合成完毕 */
// 	ret = QTTSSessionEnd(sessionID, "Normal");
// 	if (MSP_SUCCESS != ret)
// 	{
// 		printf("QTTSSessionEnd failed, error code: %d.\n",ret);
// 	}

// 	return ret;
// }

// void play_test1()
// {
//     if (SDL_Init(SDL_INIT_AUDIO) < 0) {
//         SDL_Log("Unable to initialize SDL: %s", SDL_GetError());
//         return 1;
//     }
    
//     SDL_AudioSpec wavSpec;
//     Uint32 wavLength;
//     Uint8 *wavBuffer;

//     if (SDL_LoadWAV(AUDIO_FILE_PATH, &wavSpec, &wavBuffer, &wavLength) == NULL) {
//         SDL_Log("Unable to load wav file: %s", SDL_GetError());
//         return 1;
//     }
    
//     SDL_AudioDeviceID deviceId = SDL_OpenAudioDevice(NULL, 0, &wavSpec, NULL, 0);
//     if (deviceId == 0) {
//         SDL_Log("Failed to open audio device: %s", SDL_GetError());
//         return 1;
//     }

//     if (SDL_QueueAudio(deviceId, wavBuffer, wavLength) < 0) {
//         SDL_Log("Failed to queue audio: %s", SDL_GetError());
//         return 1;
//     }
//     SDL_PauseAudioDevice(deviceId, 0);

//     // 等待音频播放完成
//     while (SDL_GetQueuedAudioSize(deviceId) > 0) {
//         SDL_Delay(100);
//     }

//     SDL_CloseAudioDevice(deviceId);
//     SDL_FreeWAV(wavBuffer);
//     SDL_Quit();

//     return 0;
// }

// void play_test2()
// {
//     if (SDL_Init(SDL_INIT_AUDIO) < 0) {
//         SDL_Log("Unable to initialize SDL: %s", SDL_GetError());
//         return 1;
//     }
    
//     SDL_AudioSpec wavSpec;
//     Uint32 wavLength;
//     Uint8 *wavBuffer;

//     if (SDL_LoadWAV("test2.wav", &wavSpec, &wavBuffer, &wavLength) == NULL) {
//         SDL_Log("Unable to load wav file: %s", SDL_GetError());
//         return 1;
//     }
    
//     SDL_AudioDeviceID deviceId = SDL_OpenAudioDevice(NULL, 0, &wavSpec, NULL, 0);
//     if (deviceId == 0) {
//         SDL_Log("Failed to open audio device: %s", SDL_GetError());
//         return 1;
//     }

//     if (SDL_QueueAudio(deviceId, wavBuffer, wavLength) < 0) {
//         SDL_Log("Failed to queue audio: %s", SDL_GetError());
//         return 1;
//     }
//     SDL_PauseAudioDevice(deviceId, 0);

//     // 等待音频播放完成
//     while (SDL_GetQueuedAudioSize(deviceId) > 0) {
//         SDL_Delay(100);
//     }

//     SDL_CloseAudioDevice(deviceId);
//     SDL_FreeWAV(wavBuffer);
//     SDL_Quit();

//     return 0;
// }
// /* int main(int argc, char* argv[])
// {
// 	play_test1();

// }
//  */

