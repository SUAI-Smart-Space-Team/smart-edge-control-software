#ifndef DEVICE_H
#define DEVICE_H
#include "DeviceInterface.h"
#include <tuple>
class Device : public DeviceInterface
{
public:
    Device();
    ~Device();
    void setValues(std::any param) override;

private:
    void setSpeed(int fanSpeedPercentage);
    void setRgb(std::string rgbstring);
    int convertPercentageToPwm(int percent);
    int port_;
};
#endif