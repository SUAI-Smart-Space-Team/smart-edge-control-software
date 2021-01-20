#include "Device.h"
//#include <wiringPi.h>
//#include <wiringSerial.h>
#include <iostream>
#include <string>
#include <tuple>

int Device::convertPercentageToPwm(int percent)
{
    return percent * 10;
}
void Device::setSpeed(int fanSpeedPercentage) {
    wiringPiSetup();
    if (fanSpeedPercentage != -1) {
        pinMode(1, PWM_OUTPUT);
        pwmWrite(1, convertPercentageToPwm(fanSpeedPercentage));
    }
}
void Device::setRgb(std::string rgbString) {
    if (!rgbString.empty()) {
        int port = serialOpen("/dev/ttyUSB0", 9600);
        if (port != -1) {
            serialPuts(port, rgbString.c_str());
            serialClose(port);
        }
        else {
            std::cerr << "Port opening error" << std::endl;
        }
    }
}

void Device::setValues(std::any param)
{
    std::string r;
    int f;
    std::tie(r,f) = std::any_cast<std::tuple<std::string,int>>(param);
    setRgb(r);
    setSpeed(f);
}
