#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <termios.h>

int main() {
    int serial_fd = open("/dev/ttyUSB0", O_RDWR);
    if (serial_fd == -1) {
        perror("无法打开串口");
        exit(1);
    }

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

    char buffer[255];
    while(1){
    int length = read(serial_fd, buffer, sizeof(buffer));
    
    if (length > 1) {
        printf("唤醒成功\n");
    }
    }
    close(serial_fd);

    return 0;
}
