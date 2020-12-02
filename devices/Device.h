#pragma once
#include "DeviceInterface.h"
class Device : public DeviceInterface
{
public:
    void setFanspeed(int fan) override;
    void setRgb(std::string rgbstring) override;
};

