all:
	g++  "main.cpp" "BusinessLogic.cpp" "devices/Device.cpp" "commands/WebCommands.cpp" -o hello -lcurl -l wiringPi
clean:	
	rm -rf devices commands
	rm  *.h *.cpp 