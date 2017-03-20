#include"I2CDevice.h"
#include<iostream>
#include<sstream>
#include<fcntl.h>
#include<iomanip>
#include<stdio.h>
#include<unistd.h>
#include<sys/ioctl.h>
#include<linux/i2c.h>
#include<linux/i2c-dev.h>
using namespace std;

#define HEX(x) setw(2) << setfill('0') << hex << (int)(x)

I2CDevice::I2CDevice(unsigned int _bus, unsigned int _device)
{
	bus=_bus;
	device=_device;
	this->open();
}

int I2CDevice::open(){
   string name;
   if(this->bus==0) name = BBB_I2C_0;
   else if(this->bus==1) name = BBB_I2C_1;
   else name = BBB_I2C_2;

   if((this->file=::open(name.c_str(), O_RDWR)) < 0){
      perror("I2C: failed to open the bus\n");
	  return 1;
   }
   if(ioctl(this->file, I2C_SLAVE, this->device) < 0){
      perror("I2C: Failed to connect to the device\n");
	  return 1;
   }
   return 0;
}

int I2CDevice::writeRegister(unsigned int registerAddress, unsigned char value){
   unsigned char buffer[2];
   buffer[0] = registerAddress;
   buffer[1] = value;
   if(::write(this->file, buffer, 2)!=2){
      perror("I2C: Failed write to the device\n");
      return 1;
   }
   return 0;
}

int I2CDevice::write(unsigned char value){
   unsigned char buffer[1];
   buffer[0]=value;
   if (::write(this->file, buffer, 1)!=1){
      perror("I2C: Failed to write to the device\n");
      return 1;
   }
   return 0;
}

unsigned char I2CDevice::readRegister(unsigned int registerAddress){
   this->write(registerAddress);
   unsigned char buffer[1];
   if(::read(this->file, buffer, 1)!=1){
      perror("I2C: Failed to read in the value.\n");
      return 1;
   }
   return buffer[0];
}

unsigned char* I2CDevice::readRegisters(unsigned int number, unsigned int fromAddress){
	this->write(fromAddress);
	unsigned char* data = new unsigned char[number];
    if(::read(this->file, data, number)!=(int)number){
       perror("IC2: Failed to read in the full buffer.\n");
	   return NULL;
    }
	return data;
}

void I2CDevice::debugDumpRegisters(unsigned int number){
	cout << "Dumping Registers for Debug Purposes:" << endl;
	unsigned char *registers = this->readRegisters(number);
	for(int i=0; i<(int)number; i++){
		cout << HEX(*(registers+i)) << " ";
		if (i%16==15) cout << endl;
	}
	cout << dec;
}

void I2CDevice::close(){
	::close(this->file);
	this->file = -1;
}

I2CDevice::~I2CDevice() {
	if(file!=-1) this->close();
}

#ifdef TEST_I2C
int main()
{
	I2CDevice test(1,0x20);	
	test.open();
	test.writeRegister(0x00, 0x00);
	test.writeRegister(0x12, 0x54);
	//test.writeRegister(0x12, 0x54);
	test.close();
	return 0;
}
#endif
