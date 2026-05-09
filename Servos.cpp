#include "Servos.h"
#include <Arduino.h>

//servo conroll (steering) 


Servos::Servos(int id){
  id = servosId; 
}

Servos::steer(int x, int y){
  x = joyX; 
  y = joyY; 

  //do steer calculations
}

