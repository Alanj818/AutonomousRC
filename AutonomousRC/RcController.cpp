#include "RcController.h"
#include <Arduino.h>

RcController::RcController(Motor* motor, Servos* servos, Lidar* lidar) : motor(motor), servos(servos), lidar(lidar) {}

void RcController::begin(){
  //controll the begin function of all three here
  motor->begin(); 
  servos->begin(); 
  lidar->begin(); 
}

void RcController::update(){
  //controll the update function of all three here
  motor->update();
  servos->update(); 
  lidar->begin(); 

  //add more functionality here, distance, traction control, anything else i could include 
}