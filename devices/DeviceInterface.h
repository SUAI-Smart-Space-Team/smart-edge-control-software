#ifndef DEVICEINTERFACE_H
#define DEVICEINTERFACE_H
#include <string>
class DeviceInterface
{
public:
	virtual void setSpeed(int fan) = 0;
	virtual void setRgb(std::string rgbstring) = 0;
};

#endif