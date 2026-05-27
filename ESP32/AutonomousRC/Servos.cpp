#include "Servos.h"
#include <Arduino.h>

//servo conroll (steering) 

Servos::Servos(int id){
  servosId = id;
  steerAngle = 90;
  rSteerAngle = 90; 
}

void Servos::steerL(int joyStick){
  static unsigned long prevJoy = 0;
  if(joyStick >= -10 && joyStick <= 10){
    steerAngle = 90;
  } else {
    steerAngle = map(joyStick, -512, 511, 70, 110);
  }

  //do steer calculations
  if(millis() - prevJoy >= 1){
    prevJoy = millis();
    servo1.write(steerAngle);
  }
}

void Servos::steerR(int joyStick){
  static unsigned long prevJoy = 0; 
  if(joyStick >= -10 && joyStick <= 10){
    rSteerAngle = 90; 
  } else {
    rSteerAngle = map(joyStick, -512, 511, 0, 180);
  }

  if(millis() - prevJoy >= 1){
    prevJoy = millis(); 
    servo2.write(rSteerAngle);
  }
}

void Servos::update(){
  Serial.printf("%8d%% %8d%% ", steerAngle, rSteerAngle);
}

void Servos::begin(){
  servo1.attach(SERVO1_PIN); //attatch the servo pin 
  servo1.setPeriodHertz(50);
  servo2.attach(SERVO2_PIN); 
  servo2.setPeriodHertz(50);
}

