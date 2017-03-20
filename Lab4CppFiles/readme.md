Beaglebone I2C Class
=====================
By Philip D. Geramian
---------------------
### pdgerami@syr.edu

The following code provides a Beaglebone I2C Class.

Release 1.1  
January 12th, 2017

Changes
-------
v1.1 
--Added test stub

Based on Code Written by Derek Molloy

Public Functions:
-----------------
###I2CDevice(unsigned int _bus, unsigned int _device)
Constructor for the I2CDevice class. It requires the bus number and device 
number. The constructor opens a file handle to the I2C device, which is 
destroyed when the destructor is called
@param bus The bus number. Usually 0, 1, or 2 on the BBB
@param device The slave ID on the bus.

###int open()
Open a connection to an I2C device 
@return 1 on failure to open to the bus or device, 0 on success.

###int writeRegister(unsigned int registerAddress, unsigned char value)
Write a single byte value to a single register.
@param registerAddress The register address
@param value The value to be written to the register
@return 1 on failure to write, 0 on success.

###int write(unsigned char value)
Write a single value to the I2C device. Used to set up the device to read 
from a particular address.
@param value the value to write to the device
@return 1 on failure to write, 0 on success.

###unsigned char readRegister(unsigned int registerAddress)
Read a single register value from the address on the device.
@param registerAddress the address to read from
@return the byte value at the register address.

###unsigned char* readRegisters(unsigned int number, unsigned int fromAddress=0)
Method to read a number of registers from a single device. This is much 
more efficient than reading the registers individually. The from address 
is the starting address to read from, which defaults to 0x00.
@param number the number of registers to read from the device
@param fromAddress the starting address to read from
@return a pointer of type unsigned char* that points to the first element 
in the block of registers

###void debugDumpRegisters(unsigned int number = 0xff)
Method to dump the registers to the standard output. It inserts a return 
character after every 16 values and displays the results in hexadecimal 
to give a standard output using the HEX() macro that is defined at the top 
of this file. The standard output will stay in hexadecimal format, hence 
the call on the last like.
@param number the total number of registers to dump, defaults to 0xff

###void close()
Close the file handles and sets a temporary state to -1.

###~I2CDevice()
Closes the file on destruction, provided that it has not already been closed.

Example Code
------------
The file I2CDevice.cpp includes a macro protected main 
function to test functionality. It makes use of I2C 2.0 
The macro is named "TEST_I2C". To use this main while 
compiling with GCC the following command can be used:

```g++ -D TEST_I2C -std=c++11 I2CDevice.cpp -o I2C_TEST```