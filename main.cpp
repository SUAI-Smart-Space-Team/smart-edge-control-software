#include "BusinessLogic.h"
#include <chrono>
#include <thread>
#include <string_view>

#include "devices/Device.h"
#include "commands/WebCommand.h"
int main() {
	constexpr std::string_view link = "http://chupr.iotfox.ru/chubrWorker.cgi?method=getTelemetry";
	WebCommand wc(link);
	Device d;
	CommandInterface& ci = wc;
	DeviceInterface& di = d;
	while (true) {
		BusinessLogic(ci, di);
		std::this_thread::sleep_for(std::chrono::milliseconds(5000));
	}
}