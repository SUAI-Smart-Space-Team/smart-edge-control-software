#pragma once
#include "DeviceInterface.h"
class Device : public DeviceInterface
{
public:
    void setFanspeed(int fan);
    void setRgb(std::string rgbstring);
};

