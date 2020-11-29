#pragma once
#include <string>
#include "CommandInterface.h"
class WebCommand : public CommandInterface {
public:
	WebCommand(const char* Link);
	void UpdateHtml();
	int getFanspeed();
	std::string getRgb();
private:
	std::string _html;
	const char* link;
};