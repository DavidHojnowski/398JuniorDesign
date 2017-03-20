#ifndef esp_H_
#define esp_H_

#include "UART.h"

using namespace std;
class esp{
	public:
		esp(int tty);
		void configEsp();
		void writeOut(const char* data);
		string readIn(int bytes);
		
		~esp();
	private:
		UART* uartDevice;
		int bytesToRead;
	
	
	
};
#endif
