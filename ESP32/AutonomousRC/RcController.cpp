#include "RcController.h"
#include <Arduino.h>

RcController::RcController(Motor* motor, Servos* servos, Lidar* lidar, GamepadInput* gamepad, Wifi* wifi, IMU* imu) : motor(motor), servos(servos), lidar(lidar), gamepad(gamepad), wifi(wifi), imu(imu) {}


//STATES

/*Explanation: If in FowardState and Want to Reverse, then you go into Wait For Reverse State, that switches to Neurtral First, then Reverse*/
/*Explanation: If in ReverseState and Want to Foward, then you go into Wait for Foward Sate, that switches to Neutral First, then Foward*/
/*Explanation: If In Foward and Want to go Foward, stay in Foward State*/
/*Explanation: If In Reverse and Want to go Reverse, stay in Reverse State*/
/*Explanation: If in Neutral and Want to Foward Or Reverse, go in Foward or Reverse State*/

//HERE BEFORE I MOVE TO HEADER FILE

enum State{
  FOWARD,
  REVERSE, 
  WAIT,
  NEUTRAL,
  BRAKE
};

State drive_state = State::NEUTRAL; //initialize to Neutral


void RcController::begin(){
  //controll the begin function of all three here
  motor->begin(); 
  servos->begin(); 
  lidar->begin(); 
  gamepad->begin();
  wifi->begin();
  imu->begin();
}


void RcController::update(){
  //controll the update function of all three here
  gamepad->update();
  int32_t throttle = gamepad->getThrottle();
  int32_t brake = gamepad->getBrake();
  joystick joyStick = gamepad->getSteer();
  const int deadzone = 30; //added a deadzone

  //3 options, Foward, Reverse or Braking
  //Foward 
  bool reqFoward = throttle > deadzone && brake <= deadzone; 

  //Reverse 
  bool reqReverse = brake > deadzone && throttle <= deadzone;

  //Brake
  bool reqBrake = brake > deadzone && throttle > deadzone;
  
  /*Explanation: This abstracts away my if statements, only 3 options for drive options realistically.*/

  //This is where we initialize the variable that will take timer input
  static unsigned long prevMillis = 0;
  static unsigned long prevUpdate = 0; 

  //BRAKE TASK
  if (reqBrake) {
    if(drive_state == State::FOWARD){
      drive_state = State::BRAKE;
    } else if(drive_state == State::REVERSE){
      drive_state = State::BRAKE;
    } else if (drive_state == State::BRAKE){
      motor->motorBrake(throttle, brake);
    }
  } 

  //FOWARD TASK
  else if (reqFoward){
    if(drive_state == State::BRAKE){
      drive_state = State::FOWARD;

    } else if (drive_state == State::FOWARD){
      motor->setThrottleSpeed(throttle);

    } else if (drive_state == State::REVERSE){
      drive_state = State::WAIT; 
      prevMillis = millis(); 

    } else if (drive_state == State::WAIT){
      motor->setSpeed(0); // go into neutral in wait and neutral state
      if(millis() - prevMillis >= 700){
        drive_state = State::NEUTRAL;
      }

    } else if (drive_state == State::NEUTRAL){
      motor->setSpeed(0);
      drive_state = State::FOWARD; 

    }
  } 

  //REVERSE TASK
  else if (reqReverse) {
    if(drive_state == State::REVERSE){
      motor->setBrakeSpeed(brake);

    } else if (drive_state == State::FOWARD){
      drive_state = State::WAIT;
      prevMillis = millis();

    } else if (drive_state == State::WAIT){
      motor->setSpeed(0);
      if(millis() - prevMillis >= 700){
        drive_state = State::NEUTRAL;
      }

    } else if (drive_state == State::NEUTRAL){
      motor->setSpeed(0); 
      drive_state = State::REVERSE;

    } else if (drive_state == State::BRAKE){
      drive_state = State::REVERSE;
    }
  } 

  //Neutral State
  else {
    drive_state = State::NEUTRAL;
    motor->setSpeed(0);
  }
  static unsigned long lastUpdate = 0;
  if(millis() - lastUpdate >= 50){
    lastUpdate = millis();
    uint16_t test_lidar = lidar->getDistance();
    wifi->sendData(test_lidar);
    imu->fillData();
  }
 
  motor->move();
  servos->steerL(joyStick.x);
  servos->steerR(joyStick.rX);

  //handle all the updates, 
  if(millis() - prevUpdate >= 1500){
    prevUpdate = millis();
    Serial.printf("%8s %8s %8s %8s %8s\n", "LeftJoy", "RightJoy", "Speed", "Throttle", "Brake");
    servos->update();
    motor->update();
    Serial.println();
    lidar->update();
    Serial.println();
    wifi->update();
    Serial.println();
    imu->update();
    Serial.println();
  }


  //add more functionality here, distance, traction control, anything else i could include 
}