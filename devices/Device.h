#ifndef DEVICE_H
#define DEVICE_H
#include "DeviceInterface.h"
class Device : public DeviceInterface
{
public:
    void setSpeed(int fan) override;
    void setRgb(std::string rgbstring) override;
};
#endif