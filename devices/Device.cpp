#include "Device.h"
#include <wiringPi.h>
#include <wiringSerial.h>
#include <iostream>
#include <string>

int Device::convertPercentageToPwm(int percent)
{
    return percent * 10;
}
void Device::setSpeed(int fanSpeedPercentage) {
    wiringPiSetup();
    pinMode(1, PWM_OUTPUT);
    pwmWrite(1, convertPercentageToPwm(fanSpeedPercentage));
}
void Device::setRgb(std::string rgbString) {
    int port = serialOpen("/dev/ttyUSB0", 9600);
    if (port != -1) {
        serialPuts(port, rgbString.c_str());
    }
    else {
        std::cerr << "Message lost" << std::endl;
    }
}