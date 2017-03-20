smart: smarthouse.cpp
	g++ -D TEST_smart -std=c++11 smarthouse.cpp I2CDevice.cpp esp.cpp UART.cpp -o smarttest

i2c: I2CDevice.cpp
	g++ -D TEST_I2C -std=c++11 I2CDevice.cpp -o i2ctest

uart: UART.cpp
	g++ -D TEST_UART -std=c++11 UART.cpp -o uarttest
	
esp: esp.cpp
	g++ -D TEST_esp -std=c++11 esp.cpp I2CDevice.cpp UART.cpp -o esptest
