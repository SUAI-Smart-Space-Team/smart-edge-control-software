#include "Device.h"
#include<wiringPi.h>
#include <fcntl.h>
#include <termios.h>
#include <unistd.h>
#include<iostream>
#include<string>

class portOpeningException : std::exception {};
bool openPort(const char* COM_name, speed_t speed,int* F_ID)
{
        
        *F_ID = open(COM_name, O_RDWR | O_NOCTTY);
        if (*F_ID == -1)
        {
            std::cerr << "error with opening port" << std::endl;
            return false;
        }
        struct termios options;
        tcgetattr(*F_ID, &options);
        cfsetispeed(&options, speed);
        cfsetospeed(&options, speed);
        options.c_cc[VTIME] = 20;
        options.c_cc[VMIN] = 0;
        options.c_cflag &= ~PARENB;
        options.c_cflag &= ~CSTOPB;
        options.c_cflag &= ~CSIZE;
        options.c_cflag |= CS8;
        options.c_lflag = 0;
        options.c_oflag &= ~OPOST;
        tcsetattr(*F_ID, TCSANOW, &options);
        return true;
}
int sendData(const char* buff, int len,int* F_ID)
{
    int n = write(*F_ID, buff, len);
    return n;
}
void closeCom(int* F_ID)
{
    close(*F_ID);
    *F_ID = -1;
}
int convertPercentageToPwm(int percent) {
    return percent * 10;
}
void Device::setSpeed(int fanSpeedPercentage)  {
    wiringPiSetup();
    pinMode(1, PWM_OUTPUT);
    pwmWrite(1, convertPercentageToPwm(fanSpeedPercentage));
}
void Device::setRgb(std::string rgbString)  {
    int F_ID = -1;
    bool res = openPort("/dev/ttyUSB0", B9600,&F_ID);
    if (res) {
        if (sendData(rgbString.c_str(), rgbString.length(),&F_ID) == -1) {
            std::cerr << "message lost" << std::endl;
        }
        closeCom(&F_ID);
    }
}