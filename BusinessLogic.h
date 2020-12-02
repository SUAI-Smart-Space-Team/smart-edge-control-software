#ifndef BUSINESSLOGIC_H
#define BUSINESSLOGIC_H
#include "devices/DeviceInterface.h"
#include "commands/CommandInterface.h"
class BusinessLogic
{
public:
	BusinessLogic(CommandInterface* c, DeviceInterface* di);
};
#endif
