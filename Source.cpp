#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include<string>
#include<iostream>
#include<C:\Users\Ananasnoe\source\repos\raspberry\curl-7.73.0-win64-mingw\include\curl\curl.h>
//#include<wiringPi.h>
#include <fcntl.h>
//#include <termios.h>
#include <errno.h>
//#include <sys/ioctl.h>
//#include <unistd.h>
using namespace std;
int F_ID = -1;
string SampleString(string arg, int nach, int kon) {
    string str;
    for (int i = nach + 1; i < kon; i++) {
        str = str + arg[i];
    }
    return str;
}
/*bool openPort(const char* COM_name, speed_t speed)
{
    F_ID = open(COM_name, O_RDWR | O_NOCTTY);
    if (F_ID == -1)
    {
        char* errmsg = strerror(errno);
        printf("%s\n", errmsg);
        return false;
    }
    struct termios options; ///структура для установки порта
    tcgetattr(F_ID, &options); //читает пораметры порта

    cfsetispeed(&options, speed); //установка скорости порта
    cfsetospeed(&options, speed); //установка скорости порта

    options.c_cc[VTIME] = 20; //Время ожидания байта 20*0.1 = 2 секунды
    options.c_cc[VMIN] = 0; //минимальное число байт для чтения


    options.c_cflag &= ~PARENB; //бит четности не используется
    options.c_cflag &= ~CSTOPB; //1 стоп бит
    options.c_cflag &= ~CSIZE;  //Размер байта
    options.c_cflag |= CS8;  //8 бит

    options.c_lflag = 0;
    options.c_oflag &= ~OPOST; //Обязательно отключить постобработку

    tcsetattr(F_ID, TCSANOW, &options); //сохронения параметров порта

    return true;
}*/
/*int sendData(unsigned char* buff, int len)
{
    int n = write(F_ID, buff, len);
    if (n == -1)
    {
        char* errmsg = strerror(errno);
        printf("%s\n", errmsg);
    }
    return n;
}*/
/*void closeCom(void)
{
    close(F_ID);
    F_ID = -1;
    return;
}*/
static size_t write_data(char* ptr, size_t size, size_t nmemb, string* data)
{
    if (data)
    {
        data->append(ptr, size * nmemb);
        return size * nmemb;
    }
    else
        return 0;  // будет ошибка
}
class Value {
public:
    Value() {
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
        string fanspeed = SampleString(_html, nach, kon);// вырезаем строку
        cout << "fanspeed " << fanspeed << endl;
        int fan = stoi(fanspeed);
        cout << "Fan percentage: " << fan << endl;
        return fan;
    }
    string getRgbstring() {
        int nach = _html.find("pumpColor");
        nach = _html.find(":", nach);
        nach = _html.find("\"", nach);
        int kon = _html.find("\"", nach + 1);
        string pumpColor = SampleString(_html, nach, kon);
        nach = _html.find("coolerColor");
        nach = _html.find(":", nach);
        nach = _html.find("\"", nach);
        kon = _html.find("\"", nach + 1);
        string coolerRgb = SampleString(_html, nach, kon);
        return pumpColor + " " + coolerRgb;
    }
private:
    string _html;
};
int main() {
    while (1) {
        Value test;
        int fan = test.getFanspeed();
        string rgb = test.getRgbstring();
        /*wiringPiSetup();
        pinMode(1, PWM_OUTPUT);
        pwmWrite(1, fan * 10);*/
        /*bool res = openPort("/dev/ttyUSB0", B9600);
        if (!res)
        {
            printf("Невозможно открыть COM порт\n");
            return 0;
        }*/
        /*unsigned char coolerBuff[rgbstring.length() + 1];
        memcpy(coolerBuff, rgbstring.c_str(), rgbstring.size() + 1);
        cout << "Pump and cooler colors: " << coolerBuff << endl;
        sendData(coolerBuff, rgbstring.length() + 1);
        closeCom();*/
    }
    return 0;
}
