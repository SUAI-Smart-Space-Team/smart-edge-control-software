#include "devices/Device.h"
#include "commands/WebCommand.h"
#include "BusinessLogic.h"
const char* Link = "http://chupr.iotfox.ru/chubrWorker.cgi?method=getTelemetry";
int main() {
	
		CommandInterface* ci = new WebCommand(Link);
		DeviceInterface* di = new Device();
		while (1) {
			BusinessLogic(ci, di);
		}
		delete(ci);
		delete(di);
	
	return 0;
}