#include "BusinessLogic.h"
BusinessLogic::BusinessLogic(CommandInterface* ci, DeviceInterface* di) {
	int temp = ci->getFanspeed();
	if ( temp != -1) {
		di->setSpeed(temp);
	}
	di->setRgb(ci->getRgb());
}