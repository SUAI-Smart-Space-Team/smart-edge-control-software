#include "WebCommand.h"
#include <chrono>
#include <thread>

static size_t write_data(char* ptr, const size_t size, const size_t nmemb, std::string& data) {
    data = static_cast<std::string>(ptr);
    return size * nmemb;
}

WebCommand::WebCommand(const std::string_view link): link_(static_cast<std::string>(link)) {
    curl_ = curl_easy_init();
    while (curl_ == nullptr) {
        curl_ = curl_easy_init();
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
    curl_easy_setopt(curl_, CURLOPT_URL, link_.c_str());
    curl_easy_setopt(curl_, CURLOPT_WRITEFUNCTION, write_data);
}

void WebCommand::UpdateHtml() {
    curl_easy_setopt(curl_, CURLOPT_WRITEDATA, &html_);
    curl_easy_perform(curl_);
}

std::any WebCommand::getValues() {
    UpdateHtml();
    return std::make_tuple(getRgb(), getFanspeed());
}

std::string WebCommand::findValue(std::string parameter) const { 
    return findValue(parameter, html_);
}

std::string WebCommand::findValue(std::string parameter, std::string source)
{
    int from = source.find(parameter);
    if (source.find(parameter, from + 1) != std::string::npos) {
        throw std::invalid_argument(source.c_str());
    }
    from = source.find(':', from);
    from = source.find('\"', from);
    const int to = source.find('\"', from + 1);
    const auto quote = "%22";
    if (source.find(quote, from + 1, to - from - 1) == std::string::npos) {
        return source.substr(from + 1, to - from - 1);
    }
    else {
        throw std::invalid_argument(source.c_str());
    }
}

WebCommand::~WebCommand(){
    curl_easy_cleanup(curl_);
}

int WebCommand::getFanspeed() const {
    try {
        const auto fan = stoi(findValue(std::string("coolerSpeed")));
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

std::string WebCommand::getRgb() const {
    try {
        const auto pColor = findValue(std::string("pumpColor"));
        const auto cColor = findValue(std::string("coolerColor"));
        return pColor + " " + cColor;
    }
    catch (const std::invalid_argument& err) {
        std::cerr << "caught wrong argument exception with string: " << err.what();
        return "";
    }
}



