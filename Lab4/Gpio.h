#ifndef Gpio_H
#define Gpio_H
#include <string>

class Gpio{
  public:
    std::string get();
    void set(std::string outState);
    Gpio(std::string pin);
    void changeDirection(std::string dir);
    
    
  private:
    std::string _pin;
};
#endif
