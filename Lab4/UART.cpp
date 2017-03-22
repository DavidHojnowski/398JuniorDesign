#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <termios.h>
#include <string.h>
#include <string>
#include <iostream>
#include <stdlib.h>
#include "UART.h"

#define FALSE 0
#define TRUE 1

UART::UART(int tty)
{
	if (tty < 1 || tty > 5)
	{
		std::cout<<"Invalid tty param, exiting.\n";
		exit(1);
	}
	else
		_tty=tty;
}
bool UART::opendev(int baudRate, bool echo)
{
	char path[50];
	sprintf(path, "/dev/ttyO%d",_tty);
	if ((_file = open(path, O_RDWR | O_NOCTTY | O_NDELAY))<0)
	{
		std::cout<<"Failed to open TTYO"<<_tty<<". Device busy?\n";
		return FALSE;
	}
	struct termios options;
	tcgetattr(_file, &options);
	speed_t SelectedBaud[]={B50,B75,B110,B134,B150,B200,B300,B600,B1200,B1800,B2400,\
						B4800,B9600,B19200,B38400,B57600,B115200};
	int AllowedBaud[]={50,75,110,134,150,200,300,600,1200,1800,2400,4800,9600,19200,\
						38400,57600,115200};
	size_t BaudIndex;
	for (BaudIndex=0; BaudIndex<17; BaudIndex++)
	{
		if (baudRate==AllowedBaud[BaudIndex])
			break;
		else if(BaudIndex==16)
		{
			std::cout<<"Invalid Baud Rate\n";
			return FALSE;
		}
	}
	options.c_cflag = SelectedBaud[BaudIndex] | CS8 | CREAD | CLOCAL;
	if (echo=FALSE)
		options.c_lflag=0;
	options.c_iflag = IGNPAR | ICRNL;
	tcflush(_file, TCIFLUSH);
	tcsetattr(_file, TCSANOW, &options);
	_isOpen=TRUE;
	return TRUE;
}

bool UART::writemsg(const char* message)
{
	int count=0;
	if ((count = write(_file, message, strlen(message)+1))<0)
	{
		std::cout<<"Failed to write\n";
		return FALSE;
	}
	return TRUE;
}

std::string UART::readmsg(int numChar)
{
	unsigned char receive[numChar+1];
	int count=0;
	if ((count = read(_file, (void*)receive, numChar))<0)
		return "";
	if (count==0) 
		return "";
	else 
	{
		std::string output (reinterpret_cast<char*>(receive));
		output[count] = '\0';
		return output;
	}
}

bool UART::closedev()
{
	close(_file);
	_isOpen=FALSE;
}

UART::~UART()
{
	if (_isOpen==TRUE)
		closedev();
	_file=0;
	_tty=-1;
	_isOpen=FALSE;
}

#ifdef TEST_UART
int main()
{
	UART tty01(1);
	tty01.opendev(115200, FALSE);
	std::string mesg;
	//SEND AT COMMANDS
	/*tty01.writemsg("AT+CIPMUX=1\r\n");
	while ((mesg=tty01.readmsg(30))=="\0"){}
	usleep(100000);//100ms
	tty01.writemsg("AT+CIPSERVER=1\r\n");
	while ((mesg=tty01.readmsg(30))=="\0"){}
	usleep(100000);//100ms
	tty01.writemsg("AT+CWMODE=1\r\n");
	while ((mesg=tty01.readmsg(30))=="\0"){}
	usleep(100000);//100ms
	tty01.writemsg("AT+CWJAP=\"iot_lab\",\"44FEC4DDB9\"");
	while ((mesg=tty01.readmsg(40))=="\0"){}
	usleep(100000);//100ms
	//Now Send Data
	tty01.writemsg("AT+CIFSR\r\n");
	while ((mesg=tty01.readmsg(20))=="\0"){}
	usleep(100000);//100ms
*/
	//while ((mesg=tty01.readmsg(100))=="\0"){}
	//std::cout<<mesg<<std::endl;
	//tty01.writemsg("AT+CIPSEND=0,12\r\n");
	usleep(300000);//300ms
	//tty01.writemsg("Hello World!\r\n");
	usleep(200000);//200ms
	//while ((mesg=tty01.readmsg(100))=="\0"){} //receive hello world dank memes back
	//std::cout<<mesg<<std::endl;
	usleep(200000);//200ms
	while(true){
	while ((mesg=tty01.readmsg(20))=="\0"){} //receive message from PuTTy
	//mesg = mesg.substr(12);
	//mesg[14] = '\0';
	mesg += 9;
	std::cout<<mesg<<std::endl;
	}
	return 0;
}
#endif
