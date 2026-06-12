#ifndef RCCON_H
#define RCCON_H
#include "Motor.h"
#include "Lidar.h"
#include "Servos.h"
#include "GamepadInput.h"
#include "Wifi.h"

class RcController{
  public:
    RcController(Motor* mo, Servos* s, Lidar* l, GamepadInput* g, Wifi* w);

    void begin(); 
    void update(); 

  private:
    Motor* motor; 
    Servos* servos; 
    Lidar* lidar; 
    GamepadInput* gamepad;
    Wifi* wifi;
};

#endif