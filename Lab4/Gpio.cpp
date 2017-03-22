#include "Gpio.h"
#include <iostream>
#include <string>
#include <fstream>
#include <string.h>

Gpio::Gpio(std::string pin){
  _pin = pin;
  std::ofstream myfile("/sys/class/gpio/export");
  if(myfile.is_open()){
  	myfile << _pin;
  	myfile.close();
  }
}

void Gpio::changeDirection(std::string dir){
  std::string directory ("/sys/class/gpio/gpio");
  std::string stringDirection ("/direction");
  std::string fileName;
  fileName =  directory + _pin + stringDirection;
    std::ofstream myfile(fileName);
  if(myfile.is_open()){
  	myfile << dir;
  	myfile.close();
  }
  return;
}

std::string Gpio::get(){
  std::string line;  
  std::string directory ("/sys/class/gpio/gpio");
  std::string stringValue ("/value");
  std::string fileName;
  fileName =  directory + _pin + stringValue;
  std::ifstream myfile(fileName);
  if(myfile.is_open()){
    getline(myfile,line);
    myfile.close();
  }
  return line;
}

void Gpio::set(std::string outState){
  std::string directory ("/sys/class/gpio/gpio");
  std::string stringValue ("/value");
  std::string fileName;
  fileName =  directory + _pin + stringValue;
  std::ofstream myfile(fileName);
  if(myfile.is_open()){
  	myfile << outState;
  	myfile.close();
  }
  return;
}


#ifdef TEST_Gpio
using namespace std;
int main()
{
  Gpio gpioIn("70");
  Gpio gpioOut("72");
  string value;
  while(true){
  value = gpioIn.get();
  gpioOut.set(value);
  }
  return 0;
}
#endif
