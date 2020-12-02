#ifndef COMMANDINTERFACE_H
#define COMMANDINTERFACE_H
#include <string>
#include <iostream>
class CommandInterface
{
public:
	virtual std::string getRgb() = 0;
	virtual int getFanspeed() = 0;
};

#endif