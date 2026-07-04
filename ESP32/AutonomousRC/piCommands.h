#ifndef PI_H
#define PI_H

#define PI_PIN 21
#include <Arduino.h>

//Will be using UART to communicate with the Raspberry Pi

class piCommands{
  public: 
    piCommands();
    void begin();
    void getCommands();
    void update();
  
  private:
    HardwareSerial pi;
    int8_t bits[5];
    int8_t throttle = 0;
    int8_t steering = 0;
    int8_t brake = 0;
};

#endif