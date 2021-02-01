#ifndef DEVICE_H
#define DEVICE_H
#include "DeviceInterface.h"
class Device : public DeviceInterface
{
public:
    Device();
    ~Device();
    void setValues(std::any param);

private:
    void setSpeed(int fan);
    void setRgb(std::string rgbstring);
    int convertPercentageToPwm(int percent);
    int port;
};
#endif