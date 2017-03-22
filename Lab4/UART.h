#ifndef BB_UART_H
#define BB_UART_H

#include <string>
class UART
{
	public:
		UART(){}
		UART(int tty);
		bool opendev(int baudRate, bool echo);
		bool writemsg(const char* message);
		std::string readmsg(int numChar);
		bool closedev();
		~UART();
	private:
		int _tty;
		int _file;
		bool _isOpen;
};
#endif
