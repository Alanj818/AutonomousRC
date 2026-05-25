#ifndef SERVOS_H
#define SERVOS_H

#define SERVO1_PIN 15
#define SERVO2_PIN 14

#include <ESP32Servo.h>

class Servos{
  public:
    Servos(int id);

    void steerL(int joyStick); //using joystic for this, x coordinates matter most 
    void update();
    void begin();
    void steerR(int joyStick);
  private: 
    Servo servo1; //steering 
    Servo servo2; //gonna mount lidar camera on this one
    int steerAngle; // stores the steering Angle from 0 to 180
    int servosId;   //stores servoId (don't need this yet I think)
    int rSteerAngle;
    
};
#endif