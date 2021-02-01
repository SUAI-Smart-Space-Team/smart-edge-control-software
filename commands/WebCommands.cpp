#include "WebCommand.h"

static size_t write_data(char* ptr, size_t size, size_t nmemb, std::string& data) {
    data = (std::string)ptr;
    return size * nmemb;
}

WebCommand::WebCommand(std::string_view Link): link((std::string)Link) {
    curl = curl_easy_init();
    while (curl == NULL) {
        curl = curl_easy_init();
    }
    curl_easy_setopt(curl, CURLOPT_URL, link.c_str());
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_data);
}

void WebCommand::UpdateHtml() {
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &_html);
    curl_easy_perform(curl);
}

std::any WebCommand::getValues() {
    WebCommand::UpdateHtml();
    return std::make_tuple(getRgb(), getFanspeed());
}

std::string WebCommand::findValue(std::string parameter) {
    int from = _html.find(parameter);
    if (_html.find(parameter, from + 1) != std::string::npos) {
        throw std::invalid_argument(_html.c_str());
    }
    from = _html.find(':', from);
    from = _html.find("\"", from);
    int to = _html.find("\"", from + 1);
    const char* quote = "%22";
    if (_html.find(quote, from + 1, to - from - 1) == std::string::npos) {
        return _html.substr(from + 1, to - from - 1);
    }
    else {
        throw std::invalid_argument(_html.c_str());
    }
}

WebCommand::~WebCommand(){
    curl_easy_cleanup(curl);
}

int WebCommand::getFanspeed() {
    try {
        int fan = stoi(findValue(std::string("coolerSpeed")));
        if (fan < 0 || fan > 100) {
            std::cerr << "wrong fan speed: " << fan << "\n";
            return -1;
        }
        return fan;
    }
    catch (const std::invalid_argument& err) {
        std::cerr << "caught wrong argument exception with string: " << err.what();
        return -1;
    }
    catch (const std::out_of_range& err) {
        std::cerr << "caught out of range exception with string: " << err.what();
        return -1;
    }
}

std::string WebCommand::getRgb() {
    try {
        std::string pColor = findValue(std::string("pumpColor"));
        std::string cColor = findValue(std::string("coolerColor"));
        return pColor + " " + cColor;
    }
    catch (const std::invalid_argument& err) {
        std::cerr << "caught wrong argument exception with string: " << err.what();
        return "";
    }
}



