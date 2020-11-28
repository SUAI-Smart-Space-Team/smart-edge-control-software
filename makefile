all:
	g++  "main.cpp" "BusinessLogic.cpp" "devices/Device.cpp" "commands/WebCommands.cpp" -o hello -lcurl -l wiringPi
clean:	
	rm -r devices commands
	rm  "*.h" "*.cpp" 