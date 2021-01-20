#include "BusinessLogic.h"

BusinessLogic::BusinessLogic(CommandInterface& ci, DeviceInterface& di) {
	di.setValues(ci.getValues());
}