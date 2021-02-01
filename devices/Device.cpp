#include "Device.h"
#include <wiringPi.h>
#include <wiringSerial.h>
#include <chrono>
#include <thread>

int Device::convertPercentageToPwm(int percent)
{
    return percent * 10;
}
void Device::setSpeed(int fanSpeedPercentage) {
    if (fanSpeedPercentage != -1) {
        pwmWrite(1, convertPercentageToPwm(fanSpeedPercentage));
    }
}
void Device::setRgb(std::string rgbString) {
    if (!rgbString.empty()) {
            serialPuts(port, rgbString.c_str());
    }
}

Device::Device()
{
    wiringPiSetup();
    pinMode(1, PWM_OUTPUT);
    port = serialOpen("/dev/ttyUSB0", 9600);
    do {
        port = serialOpen("/dev/ttyUSB0", 9600);
        if (port == -1){ 
            std::cerr << "failed to open port,trying again\n";
            std::this_thread::sleep_for(std::chrono::milliseconds(100)); 
        }
    } while (port == -1);
}

Device::~Device()
{
    serialClose(port);
}

void Device::setValues(std::any param)
{
    std::string r;
    int f;
    std::tie(r,f) = std::any_cast<std::tuple<std::string,int>>(param);
    setRgb(r);
    setSpeed(f);
}
