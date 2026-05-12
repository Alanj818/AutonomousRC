#include "RcController.h"
#include <Arduino.h>

RcController::RcController(Motor* motor, Servos* servos, Lidar* lidar, GamepadInput* gamepad) : motor(motor), servos(servos), lidar(lidar), gamepad(gamepad) {}

void RcController::begin(){
  //controll the begin function of all three here
  motor->begin(); 
  servos->begin(); 
  lidar->begin(); 
  gamepad->begin();
}

void RcController::update(){
  //controll the update function of all three here
  gamepad->update();
  int32_t throttle = gamepad->getThrottle();
  int32_t brake = gamepad->getBrake();
  
if (throttle > 0 && brake > 0) {
  motor->motorBrake(throttle, brake);
} 
else if (throttle > 0) {
  motor->setThrottleSpeed(throttle);
} 
else if (brake > 0) {
  motor->setBrakeSpeed(brake);
} 
else {
  motor->setSpeed(0);
}
  motor->update();

  //add more functionality here, distance, traction control, anything else i could include 
}