
## 描述
这是一个使用亚博智能科大讯飞语音模块的demo

## 使用说明
### 环境的配置
1、执行命令
~~~
lsusb
~~~
找到1a86:7523，然后，我们编辑一个文件
~~~
sudo gedit /etc/udev/rules.d/xfspeech.rules
~~~
把以下内容复制到里边，
~~~
KERNEL=="ttyUSB*",ATTRS{idVendor}=="1a86",ATTRS{idProduct}=="7523", MODE:="0777", SYMLINK+="xfserial"
~~~
保存后退出，然后输入以下命令，给xfspeech.rules执行权限，
~~~
sudo chmod a+x /etc/udev/rules.d/xfspeech.rules
~~~
输入以下三句命令，重新拔插语音板子设备，
~~~
sudo udevadm trigger
sudo service udev reload 
sudo service udev restart 
~~~
输入以下命令，检查是否成功绑定设备号，
~~~
ll /dev/xfserial
~~~
检查是否出现ttyUSB*,这个不同设备不一样，例如是ttyUSB0,将其复制然后到Serial—_open里面更改

2、动态库的移植

cd 到libs/x64文件夹下，然后执行
~~~
sudo cp lib* /usr/lib
~~~

3、编译前执行
~~~
sudo apt-get install libasound2-dev
~~~

### 编译运行
1、编译：cd到main_sample,然后make

2、运行：cd到bin文件夹，然后运行
~~~
./as
~~~

### 离线唤醒词的更换
请参考：https://www.yahboom.com/build.html?id=5769&cid=555

### 离线命令词的更换
bin文件夹下的bnf可以进行修改，具体修改语法可参考：https://bbs.xfyun.cn/thread/7595

## 演示效果
唤醒+命令词识别+播放相应的语音（或者执行相应的命令）

## 可能遇到的报错
1、fatal error: SDL2/SDL.h: 没有那个文件或目录
~~~
sudo apt-get update
sudo apt-get install libsdl2-dev
~~~
参考：https://cloud.tencent.com.cn/developer/information/%E5%A6%82%E4%BD%95%E5%9C%A8linux%E4%B8%AD%E4%BD%BF%E7%94%A8SDL%EF%BC%9F

2、fatal error: nlohmann/json.hpp: 没有那个文件或目录
~~~
sudo apt-get install nlohmann-json3-dev
~~~
参考：https://zhuanlan.zhihu.com/p/654250678


3、找不到串口ttyusb
参考：https://www.jb51.net/LINUXjishu/799104.html

sensor_serial:用来读传感器数据
xf：用来作语音识别

