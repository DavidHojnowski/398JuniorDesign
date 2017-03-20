#include <iostream>
#include <string.h>
#include <cstdio>
#include <unistd.h>
#include "I2CDevice.h"
#include "esp.h"

using namespace std;

#define FALSE 0
#define TRUE 1

esp::esp(int tty){
	uartDevice = new UART(tty);
	bytesToRead = 35;
	configEsp();
	
}


void esp::configEsp(){
	uartDevice->opendev(115200, FALSE);
	string mesg;
		//SEND AT COMMANDS
	uartDevice->writemsg("AT+CIPMUX=1\r\n");
	mesg =readIn(bytesToRead);
	usleep(100000);
	uartDevice->writemsg("AT+CIPSERVER=1\r\n");
	mesg =readIn(bytesToRead);
	usleep(100000);
	uartDevice->writemsg("AT+CWMODE=1\r\n");
	mesg =readIn(bytesToRead);
	usleep(100000);
	tty01.writemsg("AT+CWJAP=\"iot_lab\",\"44FEC4DDB9\"");
	mesg =readIn(bytesToRead);
	usleep(100000);
	
	uartDevice->writemsg("AT+CIFSR\r\n");
	mesg =readIn(bytesToRead);
	usleep(100000);	
	//will print out the IP addres we need to use 
	mesg =readIn(100);
	cout<<mesg<<std::endl;
}


string esp::readIn(int bytes){
	string mesg;
	while ((mesg=uartDevice->readmsg(bytes))=="\0"){}
	usleep(100000);
	return mesg;
	
	
}

void esp::writeOut(const char* data){
	//need c++ code 
	string mesg;
	int numBytes = (int) strlen(data);
	//need c++ code 
	string bytes = to_string(numBytes);
	string str = "AT+CIPSEND=0,"+bytes+"\r\n";
	char* send = new char[str.length() + 1];
	strcpy(send, str.c_str());
	
	uartDevice->writemsg(send);
	while ((mesg=uartDevice->readmsg(50))=="\0"){}
	usleep(100000);
	uartDevice->writemsg(data);
	while ((mesg=uartDevice->readmsg(50))=="\0"){}
	usleep(100000);
	return;
}

esp::~esp(){
	if(uartDevice !=NULL){
		delete(uartDevice);
	}
}

#ifdef TEST_esp
using namespace std;

int main(){
	esp ESP(1);
	const char* outData = "Hellllllooooo";
	ESP.writeOut(outData);
	ESP.readIn(30);
	
	I2CDevice test(1,0x20);	
	test.open();
	test.writeRegister(0x00, 0x00);
	while(true){
	string result = ESP.readIn(30);
	int i = 1, n = result.length();
	cout << "length is " << n << endl;
	bool read = true, start = false;
	string res = "";
	
	
	while(read && i < n){
		if(result[i-1] == ':')
			start = true;
		if(start && result[i] != '\n'){
			res.push_back(result[i]);
		}
		if(start && result[i] == '\n')
			break;
		++i;
	}
	
	cout << "res is " << res << endl;
	if(res != ""){
		int ch = stoi(res, nullptr, 16);
	
		cout << ch << endl;

		test.writeRegister(0x12, ch);
		//test.writeRegister(0x12, 0x54);
	}
	
	//cout << ESP.readIn(30) << endl;
	}
	test.close();
}
#endif
