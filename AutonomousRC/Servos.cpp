#include "Servos.h"
#include <Arduino.h>

//servo conroll (steering) 

Servos::Servos(int id){
  servosId = id;
  steerAngle = 90;
}

void Servos::steer(int joyStick){
  if(joyStick >= -10 && joyStick <= 10){
    steerAngle = 90;
  } else {
    steerAngle = map(joyStick, -512, 511, 0, 180);
  }
  
  //do steer calculations
  servo1.write(steerAngle);
  delay(1);
}

void Servos::update(){
  Serial.println("Servos Update Simulated");
  Serial.println();
  Serial.print("Steering angle: "); 
  Serial.print(steerAngle);
  Serial.print("%");
}

void Servos::begin(){
  servo1.attach(SERVO_PIN); //attatch the servo pin 
  ESP32PWM::allocateTimer(0);
  ESP32PWM::allocateTimer(1);
  ESP32PWM::allocateTimer(2);
  ESP32PWM::allocateTimer(3);
  servo1.setPeriodHertz(50);
}

