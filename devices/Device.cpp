#include "Device.h"
#include <chrono>
#include <thread>
#include <wiringPi.h>
#include <wiringSerial.h>

int Device::convertPercentageToPwm(const int percent)
{
    return percent * 10;
}
void Device::setSpeed(const int fanSpeedPercentage) {
    if (fanSpeedPercentage != -1) {
        pwmWrite(1, convertPercentageToPwm(fanSpeedPercentage));
    }
}
void Device::setRgb(const std::string rgbString) {
    if (!rgbString.empty()) {
            serialPuts(port_, rgbString.c_str());
    }
}

Device::Device()
{
    wiringPiSetup();
    pinMode(1, PWM_OUTPUT);
    do {
        port_ = serialOpen("/dev/ttyUSB0", 9600);
        if (port_ == -1){ 
            std::cerr << "failed to open port,trying again\n";
            std::this_thread::sleep_for(std::chrono::milliseconds(5000)); 
        }
    } while (port_ == -1);
}

Device::~Device()
{
    serialClose(port_);
}

void Device::setValues(std::any param)
{
    std::string r;
    int f;
    std::tie(r,f) = std::any_cast<std::tuple<std::string,int>>(param);
    setRgb(r);
    setSpeed(f);
}
