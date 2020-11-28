#pragma once
#include "../DeviceInterface.h"
class Device :
    public DeviceInterface
{
    void setFanspeed(int fan);
    void setRgb(std::string rgbstring);
};

