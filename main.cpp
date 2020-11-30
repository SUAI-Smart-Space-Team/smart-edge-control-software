#include "BusinessLogic.h"

#include "devices/Device.h"
#include "commands/WebCommand.h"
int main() {
	std::string Link = "http://chupr.iotfox.ru/chubrWorker.cgi?method=getTelemetry";
		CommandInterface* ci = new WebCommand(Link);
		DeviceInterface* di = new Device();
		while (true) {
			try {
				BusinessLogic(ci, di);
			}
            catch (std::invalid_argument& err) {
                std::cerr << "caught wrong argument exception with string: " << err.what();
                return 0;
            }
            catch (std::out_of_range& err) {
                std::cerr << "caught out of range exception with string: " << err.what();
                return 0;
            }
            catch (int a) {
				std::cerr << "error with opening port";
            }
		}
	return 0;
}