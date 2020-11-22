#include "Device interface.h"
#include<wiringPi.h>
#include <fcntl.h>
#include <termios.h>
#include <errno.h>
#include <sys/ioctl.h>
#include <unistd.h>
#include<iostream>
#include<string>
using namespace std;
int F_ID = -1;

bool openPort(const char* COM_name, speed_t speed)
{
    F_ID = open(COM_name, O_RDWR | O_NOCTTY);
    if (F_ID == -1)
    {
        char* errmsg = strerror(errno);
        printf("%s\n", errmsg);
        return false;
    }
    struct termios options; 
    tcgetattr(F_ID, &options); 
    cfsetispeed(&options, speed);
    cfsetospeed(&options, speed); 
    options.c_cc[VTIME] = 20; 
    options.c_cc[VMIN] = 0; 
    options.c_cflag &= ~PARENB; 
    options.c_cflag &= ~CSTOPB; 
    options.c_cflag &= ~CSIZE;  
    options.c_cflag |= CS8;  
    options.c_lflag = 0;
    options.c_oflag &= ~OPOST;
    tcsetattr(F_ID, TCSANOW, &options); 
    return true;
}
int sendData(unsigned char* buff, int len)
{
    int n = write(F_ID, buff, len);
    if (n == -1)
    {
        char* errmsg = strerror(errno);
        printf("%s\n", errmsg);
    }
    return n;
}
void closeCom(void)
{
    close(F_ID);
    F_ID = -1;
    return;
}
class Device: public DeviceInterface
{
public:
    void setFanspeed(int fan) {
        wiringPiSetup();
        pinMode(1, PWM_OUTPUT);
        pwmWrite(1, fan * 10);
	}
    void setRgb(string rgbstring) {
       bool res = openPort("/dev/ttyUSB0", B9600);
       if (!res)
       {
           printf("Íåâîçìîæíî îòêðûòü COM ïîðò\n");
       }
       unsigned char* coolerBuff = new unsigned char[rgbstring.length() + 1];
       memcpy(coolerBuff, rgbstring.c_str(), rgbstring.size() + 1);
       cout << "Pump and cooler colors: " << coolerBuff << endl;
       sendData(coolerBuff, rgbstring.length() + 1);
       closeCom();
    }


};

