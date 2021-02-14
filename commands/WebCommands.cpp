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
    WebCommand::UpdateHtml();
    return std::make_tuple(getRgb(), getFanspeed());
}

std::string WebCommand::findValue(std::string parameter) {
    int from = html_.find(parameter);
    if (html_.find(parameter, from + 1) != std::string::npos) {
        throw std::invalid_argument(html_.c_str());
    }
    from = html_.find(':', from);
    from = html_.find('\"', from);
    const int to = html_.find('\"', from + 1);
    const auto quote = "%22";
    if (html_.find(quote, from + 1, to - from - 1) == std::string::npos) {
        return html_.substr(from + 1, to - from - 1);
    }
    else {
        throw std::invalid_argument(html_.c_str());
    }
}

WebCommand::~WebCommand(){
    curl_easy_cleanup(curl_);
}

int WebCommand::getFanspeed() {
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

std::string WebCommand::getRgb() {
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



