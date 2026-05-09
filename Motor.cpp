#include "Motor.h"
#include <Arduino.h>

//Motor Control

Motor::Motor(int id){
  id = motorId; 
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