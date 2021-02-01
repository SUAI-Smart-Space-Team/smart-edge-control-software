#ifndef WEBCOMMAND_H
#define WEBCOMMAND_H
#include "CommandInterface.h"

#include <curl/curl.h>
#include <tuple>

class WebCommand : public CommandInterface {
public:
	explicit WebCommand(std::string_view Link);
	void UpdateHtml();
	std::any getValues() override;
	int getFanspeed();
	std::string getRgb();
	std::string findValue(std::string parameter);
	~WebCommand();
private:
	CURL* curl;
	std::string _html;
	std::string link;
};
#endif