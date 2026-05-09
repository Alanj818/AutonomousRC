#ifndef RCCON_H
#define RCCON_H
#include "Motor.h"
#include "Lidar.h"
#include "Servos.h"

class RcController{
  public:
    RcController(Motor* mo, Servos* s, Lidar* l);

    void begin(); 
    void update(); 

  private:
    Motor* motor; 
    Servos* servos; 
    Lidar* lidar; 
};

#endif