#ifndef GAMEINPUT_H
#define GAMEINPUT_H

//using bluepad32 library for connecting xbox/ps5 controllers
#include <Bluepad32.h>

struct joystick{
  int32_t x = 0; 
  int32_t y = 0;
  int32_t rX = 0; 
  int32_t rY = 0;
};

class GamepadInput{
  public:
    void begin();
    void update();

    bool isConnected();
    int32_t getThrottle();
    int32_t getBrake();
    joystick getSteer();
    void setController(ControllerPtr ctl); 
    void clearController(ControllerPtr ctl);


  private:
    ControllerPtr controller = nullptr; 
    int32_t throttle = 0; 
    int32_t brake = 0;
    int32_t joyY = 0; 
    int32_t joyX = 0; 
    int32_t rjoyX = 0;
    int32_t rjoyY = 0;


};

#endif