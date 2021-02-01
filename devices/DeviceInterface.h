#ifndef DEVICEINTERFACE_H
#define DEVICEINTERFACE_H
#include <iostream>
#include <string>
#include <any>
class DeviceInterface
{
public:
	virtual void setValues(std::any param) = 0;
};

#endif