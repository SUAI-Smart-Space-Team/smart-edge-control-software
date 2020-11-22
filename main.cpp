#include"Device interface.h"
#include"Command interface.h"

class Logic : virtual public Device, virtual public Interface {
	
};
int main() {
	Logic value;
	value.setFanspeed(value.getFanspeed());
	value.setRgb(value.getRgb());
	return 0;
}