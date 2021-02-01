#ifndef COMMANDINTERFACE_H
#define COMMANDINTERFACE_H
#include <string>
#include <iostream>
#include <any>

class CommandInterface
{
public:
	virtual std::any getValues() = 0;
};

#endif