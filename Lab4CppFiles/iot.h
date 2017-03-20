#ifndef iot_H_
#define iot_H_
#include "esp.h"
#include "I2CDevice.h"

using namespace std;
class iot{
	public:
		iot();
		void parse();
		void send();
		
		~iot();
		
	private:
		UART* uartDevice;
		I2CDevice* I2CDevice;
		char data;
	
};
#endif
