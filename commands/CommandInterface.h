#ifndef COMMANDINTERFACE_H
#define COMMANDINTERFACE_H
#include <string>
#include <iostream>
#include <tuple>
#include <any>

class CommandInterface
{
public:
	virtual std::any getValues() = 0;
};

#endif