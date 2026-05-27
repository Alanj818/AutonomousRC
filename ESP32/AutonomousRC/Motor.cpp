#include "Motor.h"

//Motor Control

//ECS ACTS LIKE SERVO 
//1000ms - 2000ms pulse Widths from 0 throttle to 100 throttle, at 50hz

//ECS takes those pulse widths, then decides Duty Cycle 0 to 100 from there at 1700Hz

//RESTRUCTURE


Motor::Motor(int id){
  motorId = id;
}

void Motor::setSpeed(int s){
  speed = s; 
}

void Motor::setThrottleSpeed(int32_t t){
  throttle = t;
  int s = map(throttle, 0, 1024, 0, 100);
  Motor::setSpeed(s);

}

void Motor::setBrakeSpeed(int32_t b){
  brake = b;
  int s = map(brake, 0, 1024, 0, -100);
  Motor::setSpeed(s);
}

//it feels like im rewriting code here, so gonna optimize another time, currently just want this to work

void Motor::goFoward(){
  Serial.println("Go Foward Simulated"); 
  //Here we will program the motor driver to make the motor go clockwise
  int analogFoward = map(speed, 0, 100, 1500, 2000);
  //here we analogWrite(pin, analogFoward);

  esc.writeMicroseconds(analogFoward);
}

void Motor::goReverse(){
  Serial.println("Go Reverse Simulated"); 
  //Here we will program the motor driver to make the motor go counter-clockwise 
  int analogReverse = map(speed, -100, 0, 1000, 1500);
  //here we analogWrite

  esc.writeMicroseconds(analogReverse);
}

void Motor::motorBrake(int32_t throttle, int32_t brake){
  Serial.println("Brake simulated"); 

  //calculate the difference
  int brakeSpeed = map(brake, 0, 1024, 0, -100);
  int throttleSpeed = map(throttle, 0, 1024, 0, 100);



  int s = throttleSpeed + brakeSpeed;
  
  Motor::setSpeed(s); 
}

void Motor::offGas(){ 
  esc.writeMicroseconds(1500);
}

void Motor::move(){
  if(speed > 0){
    goFoward();

  } else if(speed < 0){
    goReverse();

  } else if(speed == 0){
    setSpeed(0);
    offGas();
  }
  //if its going foward, the speed should be between 0 and 100
  //if its going reverse, the speed should be between -100 and 0
  //if its braking, it should just add each other
  /*
    exmple of braking: Brake = -20, Throttle = 50, speed = 50 + -20 --> speed = 30
  */
  
}

void Motor::update(){
  //running this function should update the analog/speed values
  Serial.printf("%8d", speed);
  Serial.printf("%8d", throttle);
  Serial.printf("%8d", brake);

}

void Motor::begin(){
  //intialize motor, pins, drivers etc, maybe do a little jump foward and back 
  Serial.println("Motor Begin Simulated");
  esc.setPeriodHertz(50);
  esc.attach(MOTOR_PIN, 1000, 2000); //Pulse Widths go between 1ms to 2ms (1000us to 2000us)
  esc.writeMicroseconds(1500);
  delay(3000);
}