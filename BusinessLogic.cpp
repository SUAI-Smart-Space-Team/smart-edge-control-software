#include "BusinessLogic.h"
BusinessLogic::BusinessLogic(CommandInterface* ci, DeviceInterface* di) {
	int speed = ci->getFanspeed();
	if (speed != -1) {
		di->setSpeed(speed);
	}
	std::string color = ci->getRgb();
	if (color != "") {
		di->setRgb(color);
	}
}