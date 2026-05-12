#include "Motor.h"
#include <Arduino.h>

//Motor Control

Motor::Motor(int id){
  motorId = id;
}

void Motor::setSpeed(int s){
  speed = s; 
  if(speed > 0){
    Motor::goFoward();
  } else {
    Motor::goReverse();
  }
}

void Motor::setThrottleSpeed(int32_t t){
  throttle = t;
  int s = map(throttle, 0, 1024, 0, 100);
  Motor::setSpeed(s);
}

void Motor::setBrakeSpeed(int32_t b){
  brake = b;
  speed = map(brake, 0, 1024, 0, -100);
  Motor::setSpeed(speed);
}

//it feels like im rewriting code here, so gonna optimize another time, currently just want this to work

void Motor::goFoward(){
  Serial.println("Go Foward Simulated"); 
  //Here we will program the motor driver to make the motor go clockwise
  int analogFoward = map(throttle, 0, 1024, 0, 255);
  //here we analogWrite(pin, analogFoward);
}

void Motor::goReverse(){
  Serial.println("Go Reverse Simulated"); 
  //Here we will program the motor driver to make the motor go counter-clockwise 
  int analogReverse = map(brake, 0, 1024, 0, 255);
  //here we analogWrite
}

void Motor::motorBrake(int32_t throttle, int32_t brake){
  Serial.println("Brake simulated"); 

  //calculate the difference
  int brakeSpeed = map(brake, 0, 1024, 0, -100);
  int throttleSpeed = map(throttle, 0, 1024, 0, 100);

  speed = throttleSpeed - brakeSpeed;
  
  Motor::setSpeed(speed);
}

void Motor::offGas(){
  Serial.println("Off Gas Simulated"); 
}

void Motor::update(){
  //running this function should update the analog/speed values
  Serial.println("Motor Update Simulated");

  Serial.print("analog value of speed: "); 
  Serial.print(speed);
  Serial.print(" is -> "); 

  if(speed > 0){
    Motor::goFoward();
  } else if (speed < 0){
    Motor::goReverse();
  }
  
  int analogSpeed = map(speed, 0, 100, 0, 255) || map(speed, 0, -100, 0, 255);
  Serial.print(analogSpeed);

  //if its going foward, the speed should be between 0 and 100
  //if its going reverse, the speed should be between -100 and 0
  //if its braking, it should just add each other
  /*
    exmple of braking: Brake = -20, Throttle = 50, speed = 50 + -20 --> speed = 30
  */
}

void Motor::begin(){
  //intialize motor, pins, drivers etc, maybe do a little jump foward and back 
  Serial.println("Motor Begin Simulated");
}