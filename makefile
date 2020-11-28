all:
	g++  "main.cpp" "BusinessLogic.cpp" "Device.cpp" "Web commands.cpp" -o hello -lcurl -l wiringPi
clean:	
	rm -r devices commands
	rm  "*.h" "*.cpp" 