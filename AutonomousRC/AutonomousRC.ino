#include <Arduino.h>
#include "Battery.h"
#include "Motor.h"
#include "Servos.h"
#include "Interrupts.h"
#include "Lidar.h"
#include "RcController.h"

//virtualize hardware for now 

Motor motor(0);
Lidar lidar(0); 
Servos servos(0);

RcController controller(&motor, &servos, &lidar);


void setup(){
  Serial.begin(115200); 
  delay(500); 
  
  controller.begin();
  delay(5000); 
}

void loop(){
  controller.update();
  delay(3000);
}