#include "BusinessLogic.h"

#include "devices/Device.h"
#include "commands/WebCommand.h"
int main() {
	std::string Link = "http://chupr.iotfox.ru/chubrWorker.cgi?method=getTelemetry";
	WebCommand wc(Link);
	Device d;
	CommandInterface* ci = &wc;
	DeviceInterface* di = &d;
	while (true) {
		BusinessLogic(ci, di);
		sleep(5);
	}
	return 0;
}