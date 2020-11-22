#pragma once
#include"Web commands.cpp"
#include<string>
class Dinterface
{
public:
	virtual void setFanspeed(int fan) = 0;
	virtual void setRgb(std::string rgbstring) = 0;
};

