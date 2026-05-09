#include "Motor.h"
#include <Arduino.h>

//Motor Control

Motor::Motor(int id){
  motorId = id;
}

void Motor::goFoward(){
  Serial.println("Go Foward Simulated"); 
}

void Motor::goReverse(){
  Serial.println("Go Reverse Simulated"); 
}

void Motor::motorBrake(){
  Serial.println("Brake simulated"); 
}

void Motor::offGas(){
  Serial.println("Off Gas Simulated"); 
}

void Motor::update(){
  Serial.println("Motor Update Simulated");
}

void Motor::begin(){
  Serial.println("Motor Begin Simulated");
}