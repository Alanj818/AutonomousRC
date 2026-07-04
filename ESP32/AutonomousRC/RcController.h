#ifndef RCCON_H
#define RCCON_H
#include "Motor.h"
#include "Lidar.h"
#include "Servos.h"
#include "GamepadInput.h"
#include "Wifi.h"
#include "IMU.h"
#include "piCommands.h"

class RcController{
  public:
    RcController(Motor* mo, Servos* s, Lidar* l, GamepadInput* g, Wifi* w, IMU* i, piCommands* pi);

    void begin(); 
    void update(); 

  private:
    Motor* motor; 
    Servos* servos; 
    Lidar* lidar; 
    GamepadInput* gamepad;
    Wifi* wifi;
    IMU* imu;
    piCommands* pi;
};

#endif