#include "GamepadInput.h"

static GamepadInput* gamepadInstance = nullptr;

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
  stick.rX = rjoyX; 
  stick.rY = rjoyY;
  return stick; 
}


void onConnectedController(ControllerPtr ctl){ //Bluepad32 callback function, not part of GamepadInput.h
  if(gamepadInstance != nullptr){
    gamepadInstance->setController(ctl); 
    Serial.print("Controller Connected");
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

void GamepadInput::update() {
  bool dataUpdated = BP32.update();

  if (!dataUpdated) {
    return;  
  }

  if (controller != nullptr && controller->isConnected() && controller->hasData()) {
    throttle = controller->throttle();
    brake = controller->brake();
    joyY = controller->axisY();
    joyX = controller->axisX();
    rjoyX = controller->axisRX();
    rjoyY = controller->axisRY();
  }

  if (controller == nullptr || !controller->isConnected()) {
  throttle = 0;
  brake = 0;
  joyY = 0;
  joyX = 0;
  rjoyX = 0; 
  rjoyY = 0;
  return;
}
}


void GamepadInput::begin(){
  gamepadInstance = this;
  BP32.setup(&onConnectedController, &onDisconnectedController);
  BP32.forgetBluetoothKeys();
  BP32.enableVirtualDevice(false);
}
