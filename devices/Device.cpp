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
    if (!rgbString.empty() && !failedToOpenPort) {
            serialPuts(port_, rgbString.c_str());
    }
    else
    {
	    std::cout << rgbString;
    }
}

Device::Device()
{
    wiringPiSetup();
    pinMode(1, PWM_OUTPUT);
    int retry_count = 0;
    failedToOpenPort = false;
    do {
        port_ = serialOpen("/dev/ttyUSB0", 9600);
        if (port_ == -1){
            retry_count++;
            if (retry_count == 5)
            {
	            std::cout << "failed to open port, now writing to stdout";
                failedToOpenPort = true;
            	break;
            }
            std::cerr << "failed to open port,trying again\n";
            std::this_thread::sleep_for(std::chrono::milliseconds(5000)); 
        }
    } while (port_ == -1);
}

Device::~Device()
{
	if (!failedToOpenPort)
	{
        serialClose(port_);
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
