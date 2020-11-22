#pragma once
#include"Device.cpp"
#include <string>
#include<iostream>
using namespace std;
class Web
{
public:
	virtual string getRgb() = 0;
	virtual int getFanspeed() = 0;

};

