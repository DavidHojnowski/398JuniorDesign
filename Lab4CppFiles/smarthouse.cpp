#include <iostream>
#include <string.h>
#include <cstdio>
#include <unistd.h>
#include "I2CDevice.h"
#include "smarthouse.h"

using namespace std;

smarthouse::smarthouse(int tty){
	espDevice = new ESP(tty);
	
}

string smarthouse::read(int bytes){
	return espDevice.readIn(bytes);
}

void smarthouse::write(const char* data){
	return espDevice.writeOut(data);
}

smarthouse::~smarthouse(){
	if(espDevice !=NULL){
		delete(espDevice);
	}
}

#ifdef TEST_smart
using namespace std;

int main(){
	unsigned char dev1A;
	unsigned char dev1B;

}
#endif
