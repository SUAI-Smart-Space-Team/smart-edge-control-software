#include "BusinessLogic.h"
BusinessLogic::BusinessLogic(CommandInterface* ci, DeviceInterface* di) {
	if (int temp = ci->getFanspeed() != -1) {
		di->setSpeed(temp);
	}
	di->setRgb(ci->getRgb());
}