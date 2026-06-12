#include <Arduino.h>
#include "Battery.h"
#include "Motor.h"
#include "Servos.h"
#include "Interrupts.h"
#include "Lidar.h"
#include "RcController.h"
#include "Wifi.h"

//virtualize hardware for now 
/*
COMPONENTS: 
  brushless motors with ECMs
  Lidar camera 
  Servos
  Xbox/PS5 controller

HARDWARE: 
  motor driver
  GPIO pins
*/

Motor motor(0);
Lidar lidar(0); 
Servos servos(0);
GamepadInput gamepad;
Wifi wifi;
RcController controller(&motor, &servos, &lidar, &gamepad, &wifi);


void setup(){
  Serial.begin(115200); 
  delay(500); 
  controller.begin();
  delay(5000);
}

void loop(){
  controller.update();
  // delay(3000); //for debugging reasons, will take this away after so the loop is continuous and fast. 
}