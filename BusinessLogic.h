#pragma once
#include "Device interface.h"
#include "Command interface.h"
class BusinessLogic
{
public:
	BusinessLogic(CommandInterface* c, DeviceInterface* di);
};

