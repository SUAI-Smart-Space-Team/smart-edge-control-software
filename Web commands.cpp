#include "Command interface.h"
#include <curl/curl.h>
string SampleString(string arg, int nach, int kon) {
    string str;
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
class Interface: public Web
{
	
public:
	Interface() {
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
    int getFanspeed() {
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
private:
	string _html;
};

