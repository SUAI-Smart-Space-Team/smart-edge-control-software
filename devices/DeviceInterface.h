#ifndef DEVICEINTERFACE_H
#define DEVICEINTERFACE_H
#include <string>
#include <tuple>
#include <any>
class DeviceInterface
{
public:
	virtual void setValues(std::any param) = 0;
};

#endif