#pragma once
#include<string>
#include "Command interface.h"
class WebCommand : public CommandInterface {
public:
	WebCommand();
	int getFanspeed();
	std::string getRgb();
private:
	std::string _html;
};