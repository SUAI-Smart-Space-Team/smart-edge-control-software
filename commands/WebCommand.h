#pragma once
#include <string>
#include "CommandInterface.h"
class WebCommand : public CommandInterface {
public:
	explicit WebCommand(std::string Link);
	void UpdateHtml();
	int getFanspeed() override;
	std::string getRgb() override;
	std::string findValue(std::string parameter);
private:
	std::string _html;
	std::string link;
};