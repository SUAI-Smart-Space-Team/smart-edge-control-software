#include "BusinessLogic.h"
BusinessLogic::BusinessLogic(CommandInterface* ci, DeviceInterface* di) {
	di->setFanspeed(ci->getFanspeed());
	di->setRgb(ci->getRgb());
}