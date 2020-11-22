all:
	g++ -Wall main.cpp Device.cpp Web commands.cpp -o hello -lcurl -l wiringPi