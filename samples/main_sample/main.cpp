#include "xf.h"

int main(int argc, char* argv[])
{
    //Xunfei xunfei;

    //std::thread runThread(&Xunfei::run, &xunfei);
    //runThread.join();
    //return 0;
	XF xf;
    xf.Audio_play("欢迎.wav");
	while(1)//可以改成线程
	{
		xf.Run();      
    }
}


