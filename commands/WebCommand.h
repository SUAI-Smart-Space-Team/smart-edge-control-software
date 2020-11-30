#pragma once
#include <string>
#include "CommandInterface.h"
class WebCommand : public CommandInterface {
public:
	WebCommand(std::string Link);
	void UpdateHtml();
	int getFanspeed();
	std::string getRgb();
	std::string findValue(std::string parameter);
private:
	std::string _html;
	std::string link;
};