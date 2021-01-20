#ifndef DEVICE_H
#define DEVICE_H
#include "DeviceInterface.h"
class Device : public DeviceInterface
{
public:
    void setSpeed(int fan);
    void setRgb(std::string rgbstring);
    void setValues(std::any param);
    int convertPercentageToPwm(int percent);
};
#endif