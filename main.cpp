#include "DeviceInterface.h"
#include "CommandInterface.h"
#include "devices/Device.h"
#include "commands/Web command.h"
#include "BusinessLogic.h"
int main() {
	while (1) {
		CommandInterface* ci = new WebCommand();
		DeviceInterface* di = new Device();
		BusinessLogic(ci, di);
		delete(ci);
		delete(di);
	}
	return 0;
}