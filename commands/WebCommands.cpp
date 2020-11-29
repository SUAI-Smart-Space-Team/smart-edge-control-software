#include "WebCommand.h"
#include <curl/curl.h>
#include<iostream>
#include <string>
std::string SampleString(std::string arg, int nach, int kon) {
    std::string str;
    for (int i = nach + 1; i < kon; i++) {
        str = str + arg[i];
    }
    return str;
}
static size_t write_data(char* ptr, size_t size, size_t nmemb, std::string* data)
{
    if (data)
    {
        data->append(ptr, size * nmemb);
        return size * nmemb;
    }
    else
        return 0;  
}

WebCommand::WebCommand(const char* Link) {
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
            std::cout << _html << std::endl;       
}
int WebCommand::getFanspeed() {
    WebCommand::UpdateHtml();
        int nach = _html.find("coolerSpeed");
        nach = _html.find(":", nach);
        nach = _html.find("\"", nach);
        int kon = _html.find("\"", nach + 1);
        std::string fanspeed = SampleString(_html, nach, kon);
        std::cout << "fanspeed " << fanspeed << std::endl;
        int fan = stoi(fanspeed);
        std::cout << "Fan percentage: " << fan << std::endl;
        return fan;
}
std::string WebCommand::getRgb() {
    WebCommand::UpdateHtml();
        int nach = _html.find("pumpColor");
        nach = _html.find(":", nach);
        nach = _html.find("\"", nach);
        int kon = _html.find("\"", nach + 1);
        std::string pumpColor = SampleString(_html, nach, kon);
        nach = _html.find("coolerColor");
        nach = _html.find(":", nach);
        nach = _html.find("\"", nach);
        kon = _html.find("\"", nach + 1);
        std::string coolerRgb = SampleString(_html, nach, kon);
        return pumpColor + " " + coolerRgb;
}


