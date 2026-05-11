#include "GamepadInput.h"

GamepadInput* gamepadInstance = nullptr;

int32_t GamepadInput::getThrottle(){
  return throttle;
}

int32_t GamepadInput::getBrake(){
  return brake;
}

joystick GamepadInput::getSteer(){
  joystick stick; 
  stick.x = joyX; 
  stick.y = joyY; 
  return stick; 
}


void onConnectedController(ControllerPtr ctl){ //Bluepad32 callback function, not part of GamepadInput.h
  if(gamepadInstance != nullptr){
    gamepadInstance->setController(ctl); 
  }
}

void GamepadInput::setController(ControllerPtr ctl){
  controller = ctl;
}

void onDisconnectedController(ControllerPtr ctl){
  if(gamepadInstance != nullptr){
    gamepadInstance->clearController(ctl);
  }
}

void GamepadInput::clearController(ControllerPtr ctl){
  if(controller == ctl){
    controller = nullptr;
    throttle = 0; 
    brake = 0; 
    joyY = 0;
    joyX = 0; 
  }
}

bool GamepadInput::isConnected(){
  return controller != nullptr && controller->isConnected();
}

void GamepadInput::update(){
  BP32.update(); 
  if(controller != nullptr && controller->isConnected() && controller->hasData()){
    throttle = controller->throttle();
    brake = controller->brake();
    joyY = controller->axisY(); 
    joyX = controller ->axisX(); 
  } else{
    throttle = 0;
    brake = 0;
    joyY = 0; 
    joyX = 0; 
  }
}

void GamepadInput::begin(){
  gamepadInstance = this;
  BP32.setup(&onConnectedController, &onDisconnectedController);
  BP32.forgetBluetoothKeys();
  BP32.enableVirtualDevice(false);
}
