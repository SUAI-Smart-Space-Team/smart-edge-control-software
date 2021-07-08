all:
	g++  "main.cpp" "BusinessLogic.cpp" "devices/Device.cpp" "commands/WebCommands.cpp" -o hello -lcurl -l wiringPi -Wall -ansi -std=c++17
clean:	
	rm -rf devices commands
	rm  *.h *.cpp 

