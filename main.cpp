#include "Device interface.h"
#include "Command interface.h"
#include "Device.cpp"
#include "Web commands.cpp"
#include "BusinessLogic.h"
int main() {
	CommandInterface* ci = new WebCommand();
	DeviceInterface* di = new Device();
	BusinessLogic(ci, di);
	return 0;
}