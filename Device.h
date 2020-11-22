#pragma once
#include "Device interface.h"
class Device :
    public DeviceInterface
{
    void setFanspeed(int fan);
    void setRgb(std::string rgbstring);
};

