#pragma once
#include<string>
class DeviceInterface
{
public:
	virtual void setFanspeed(int fan) = 0;
	virtual void setRgb(std::string rgbstring) = 0;
};

