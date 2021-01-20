#ifndef BUSINESSLOGIC_H
#define BUSINESSLOGIC_H
#include "devices/DeviceInterface.h"
#include "commands/CommandInterface.h"
class BusinessLogic
{
public:
	BusinessLogic(CommandInterface& ci, DeviceInterface& di);
};
#endif
