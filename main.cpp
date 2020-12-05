#include "BusinessLogic.h"

#include "devices/Device.h"
#include "commands/WebCommand.h"
int main() {
	std::string Link = "http://chupr.iotfox.ru/chubrWorker.cgi?method=getTelemetry";
	CommandInterface* ci = new WebCommand(Link);
	DeviceInterface* di = new Device();
	while (true) {
		BusinessLogic(ci, di);
		sleep(5);
	}
	return 0;
}