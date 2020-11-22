#include "Web command.h"
#include <curl/curl.h>
#include <string>
std::string SampleString(std::string arg, int nach, int kon) {
    std::string str;
    for (int i = nach + 1; i < kon; i++) {
        str = str + arg[i];
    }
    return str;
}
static size_t write_data(char* ptr, size_t size, size_t nmemb, string* data)
{
    if (data)
    {
        data->append(ptr, size * nmemb);
        return size * nmemb;
    }
    else
        return 0;  
}


WebCommand::WebCommand() {
        while (_html == "[{\"pumpColor\":0},{\"coolerColor\":0},{\"pumpSpeed\":0},{\"coolerSpeed\":0}]") {
            CURL* curl;
            curl = curl_easy_init();
            curl_easy_setopt(curl, CURLOPT_URL, "https://suai.chupr.ru/chubrWorker.cgi?method=getConfiguration&deviceId=testStand&v=1");
            curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_data);
            curl_easy_setopt(curl, CURLOPT_WRITEDATA, &_html);
            curl_easy_perform(curl);
            curl_easy_cleanup(curl);
            cout << _html << endl;
        }
}
int WebCommand::getFanspeed() {
        int nach = _html.find("coolerSpeed");
        nach = _html.find(":", nach);
        nach = _html.find("\"", nach);
        int kon = _html.find("\"", nach + 1);
        string fanspeed = SampleString(_html, nach, kon);
        cout << "fanspeed " << fanspeed << endl;
        int fan = stoi(fanspeed);
        cout << "Fan percentage: " << fan << endl;
        return fan;
}
std::string WebCommand::getRgb() {
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


