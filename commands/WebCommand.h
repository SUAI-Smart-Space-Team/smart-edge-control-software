#ifndef WEBCOMMAND_H
#define WEBCOMMAND_H
#include <string>
#include <tuple>
#include "CommandInterface.h"
class WebCommand : public CommandInterface {
public:
	explicit WebCommand(std::string_view Link);
	void UpdateHtml();
	std::any getValues() override;
	int getFanspeed();
	std::string getRgb();
	std::string findValue(std::string parameter);
private:
	std::string _html;
	std::string link;
};
#endif