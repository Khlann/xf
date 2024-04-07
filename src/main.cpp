#include <iostream>
#include <sstream>
#include <unistd.h>
#include "LLog.h"
#include "xiaohai_robot.h"



int main(int argc, char **argv)
{
    LLOG::LLog main_log(LLOG::TLogLevel::DEBUG, "main", "./log", 400);
    std::stringstream log_data;
    log_data << u8"程序开始";
    main_log.AddLog(__LINE__, __FILE__, log_data.str().c_str(), log_data.str().size(), LLOG::TLogLevel::DEBUG);
// 
    // uint8_t temp[4] = {0x33, 0x33, 0x53, 0x40};
    // std::cout <<  std::fixed << bytesToFloat(temp) <<std::endl;
    // printf("Value: %f\n", value);
    std::string input;
    do {
        std::getline(std::cin, input);
        if (input == "exit" || input == "EXIT" || input == "Exit") 
        {
            std::cout << "Exiting program..." << std::endl;
            break;
        }
        else
        {
            std::cout << "please input (exit or EXIT): ";
        }
    } while (true);
    return 0;
}