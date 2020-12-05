#include "BusinessLogic.h"
BusinessLogic::BusinessLogic(CommandInterface* ci, DeviceInterface* di) {
	if (int temp = ci->getFanspeed() != -1) {
		di->setFanspeed(temp);
	}
	di->setRgb(ci->getRgb());
}