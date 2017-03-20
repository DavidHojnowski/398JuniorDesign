#ifndef BB_I2C_H
#define BB_I2C_H

#define BBB_I2C_0 "/dev/i2c-0"
#define BBB_I2C_1 "/dev/i2c-1"
#define BBB_I2C_2 "/dev/i2c-2"

class I2CDevice{

public:
	I2CDevice(unsigned int _bus, unsigned int _device);
	int open();
	int write(unsigned char value);
	unsigned char readRegister(unsigned int registerAddress);
	unsigned char* readRegisters(unsigned int number, unsigned int fromAddress=0);
	int writeRegister(unsigned int registerAddress, unsigned char value);
	void debugDumpRegisters(unsigned int number = 0xff);
	void close();
	~I2CDevice();
private:
	unsigned int bus;
	unsigned int device;
	int file;
};


#endif
