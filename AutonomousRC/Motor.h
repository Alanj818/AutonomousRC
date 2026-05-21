#ifndef MOTOR_H
#define MOTOR_H

#define MOTOR_PIN 18
#include <Arduino.h>
#include <ESP32Servo.h>

class Motor{
  public:
    Motor(int id); 

    void goFoward(); 
    void goReverse(); 
    void motorBrake(int32_t throttle, int32_t brake); 
    void offGas(); 
    void update(); 
    void begin(); 
    void setThrottleSpeed(int32_t throttle);
    void setBrakeSpeed(int32_t brake);
    void setSpeed(int speed);

  private: 
    int motorId;
    bool gearSwitch; 
    int speed;
    int32_t throttle;
    int32_t brake;
    Servo esc;

};

// void goFoward(); //I want this to be a button press or switch, on for drive
// void goReverse(); //I want this to be a button press or switch, off for reverse
// void brake(); //this will work with offGas
// void offGas(); //this one will simulate speed slowing down, so slowly decrease PWM, will work with brake()

#endif