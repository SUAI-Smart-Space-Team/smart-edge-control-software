#include "WebCommand.h"
#include<iostream>
#include <string>

#include <curl/curl.h>
static size_t write_data(char* ptr, size_t size, size_t nmemb, std::string* data)
{
    if (!data) return 0;
    data->append(ptr, size * nmemb);
    return size * nmemb;
}

WebCommand::WebCommand(std::string Link) {
    link = Link;
}

void WebCommand::UpdateHtml() {
    CURL* curl;
    curl = curl_easy_init();
    curl_easy_setopt(curl, CURLOPT_URL, link);
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
    return _html.substr(from + 1, to - from - 1);
}

int WebCommand::getFanspeed() {
    WebCommand::UpdateHtml();
    int fan = stoi(findValue(std::string("coolerSpeed")));
    if (fan < 0 || fan > 100) throw std::invalid_argument(""+fan);
    return fan;
}

std::string WebCommand::getRgb() {
    WebCommand::UpdateHtml();
    return findValue(std::string("pumpColor")) + " " + findValue(std::string("coolerColor"));
}



