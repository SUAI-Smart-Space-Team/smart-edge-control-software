#include "Device.h"
#include<wiringPi.h>
#include <fcntl.h>
#include <termios.h>
#include <unistd.h>
#include<iostream>
#include<string>
int F_ID = -1;

bool openPort(const char* COM_name, speed_t speed)
{
    F_ID = open(COM_name, O_RDWR | O_NOCTTY);
    if (F_ID == -1)
    {
        throw -1;
        return false;
    }
    struct termios options; 
    tcgetattr(F_ID, &options); 
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
    tcsetattr(F_ID, TCSANOW, &options); 
    return true;
}
int sendData(const char* buff, int len)
{
    int n = write(F_ID, buff, len);
    if (n == -1) throw -1;
    return n;
}
void closeCom(void)
{
    close(F_ID);
    F_ID = -1;
    return;
}
int convertPercentageToPwm(int percent) {
    return percent * 10;
}
void Device::setFanspeed(int fanSpeedPercentage) {
    wiringPiSetup();
    pinMode(1, PWM_OUTPUT);
    pwmWrite(1, convertPercentageToPwm(fanSpeedPercentage));
}
void Device::setRgb(std::string rgbString) {
    bool res = openPort("/dev/ttyUSB0", B9600);
    sendData(rgbString.c_str(), rgbString.length() + 1);
    closeCom();
}