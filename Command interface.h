#pragma once
#include <string>
#include<iostream>
using namespace std;
class CommandInterface
{
public:
	virtual string getRgb() = 0;
	virtual int getFanspeed() = 0;

};

