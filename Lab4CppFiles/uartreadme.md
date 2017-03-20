Beaglebone UART Class
=====================
By Philip D. Geramian
---------------------
### pdgerami@syr.edu

The following code provides a Beaglebone UART Class.

Release 1.1  
March 30th, 2016

Changes
--------
v1.1  
-Added the option to disable echo from the Beaglebone 
in the ``opendev()`` function.  
-Updated the test main to make use of this feature.

Public Functions:
-----------------
###UART()
This Constructor does nothing and should not be used

###UART(int tty)
This Constructor should be used at all times.
This checks to make sure the passed TTY is a valid 
device. This class only works with TTY devices named
as such: TTYO* where * equals the number you pass to 
this function. This constructor does not open the 
device.

###bool opendev(int baudRate, bool echo)
This member function opens the selected TTY device.
You may pass a standart baud rate as the parameter as
no baud rate is selected by default. Also you must 
specify if you want the UART to echo. It will return 
TRUE if successful, and FALSE if unsuccessful. 
Additionally it will print out an error message if 
unsuccessful. 

###bool writemsg(const char* message)
This member function will write the provided message
out to the TTY device. Upon successfully transmitting 
it will return TRUE, otherwise it will return FALSE.

###std::string readmsg(int numChar)
This member function will return a message on the TTY 
device with a maximum of numChar.

###bool closedev()
This member function will close the TTY device. Upon 
return if successful will return TRUE, otherwise it 
will return FALSE.

###~UART()
This Destructor will close (if needed) the TTY device 
we are using and should be manually called if allocating 
the UART on the Heap (by using 'new'), by calling delete, 
otherwise if the UART is on the stack, the destructor 
should be automatically called when the code goes out of 
scope (leaves {...}).

Example Code
------------
The file UART.cpp includes a macro protected main 
function to test functionality. The macro is named
"TEST_UART". This main makes use of /dev/ttyO1.
To use this main while compiling with 
GCC the following command can be used:

```g++ -D TEST_UART UART.cpp -o UART_TEST```
