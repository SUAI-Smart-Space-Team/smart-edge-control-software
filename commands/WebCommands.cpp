#include "WebCommand.h"
#include<iostream>
#include <string>

#include <curl/curl.h>
static size_t write_data(char* ptr, size_t size, size_t nmemb, std::string& data)
{
    if (data != "") return 0;
    data.append(ptr, size * nmemb);
    return size * nmemb;
}

WebCommand::WebCommand(std::string Link): link(Link){
 
}

void WebCommand::UpdateHtml() {
    CURL* curl;
    curl = curl_easy_init();
    curl_easy_setopt(curl, CURLOPT_URL, link.c_str());
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_data);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &_html);
    curl_easy_perform(curl);
    curl_easy_cleanup(curl);
    std::clog << _html << std::endl;       
}

std::string WebCommand::findValue(std::string parameter) {
    int from = _html.find(parameter);
    from = _html.find(":", from);
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

int WebCommand::getFanspeed() {
    WebCommand::UpdateHtml();
    try {
        int fan = stoi(findValue(std::string("coolerSpeed")));
        if (fan < 0 || fan > 100) {
            std::cerr << "wrong fan speed: " << fan << std::endl;
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
    WebCommand::UpdateHtml();
    return findValue(std::string("pumpColor")) + " " + findValue(std::string("coolerColor"));
}



