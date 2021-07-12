#ifndef WEBCOMMAND_H
#define WEBCOMMAND_H
#include "CommandInterface.h"

#include <curl/curl.h>
#include <tuple>

class WebCommand : public CommandInterface {
public:
	explicit WebCommand(std::string_view link);
	void UpdateHtml();
	std::any getValues() override;
	int getFanspeed() const;
	std::string getRgb() const;
	std::string findValue(std::string parameter) const;
	static std::string findValue(std::string parameter, std::string source);
	~WebCommand() override;
private:
	CURL* curl_;
	std::string html_;
	std::string link_;
};
#endif