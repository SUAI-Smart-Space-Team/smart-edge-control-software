#include "BusinessLogic.h"

#include "devices/Device.h"
#include "commands/WebCommand.h"
int main() {
	std::string Link = "http://chupr.iotfox.ru/chubrWorker.cgi?method=getTelemetry";
	
	while (true) {
		CommandInterface* ci = new WebCommand(Link);
		DeviceInterface* di = new Device();
		BusinessLogic(ci, di);
		delete(ci);
		delete(di);
		sleep(5);
	}
	return 0;
}