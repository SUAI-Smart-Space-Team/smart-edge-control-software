all:
	g++  "main.cpp" "BusinessLogic.cpp" "Device.cpp" "Web commands.cpp" -o hello -lcurl -l wiringPi