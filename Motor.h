#ifndef MOTOR_H
#define MOTOR_H

#define MOTOR_PIN some_pin

class Motor{
  public:
    Motor(int id); 

    void goFoward(); 
    void goReverse(); 
    void motorBrake(); 
    void OffGas(); 

  private: 
    int motorId;
    bool gearSwitch; 
    int throttle; 
    int brake; //bluepad32 uses brake(), take precauseion here for brake value 
    int bumberL; 
    int bumberR; 

}

// void goFoward(); //I want this to be a button press or switch, on for drive
// void goReverse(); //I want this to be a button press or switch, off for reverse
// void brake(); //this will work with offGas
// void offGas(); //this one will simulate speed slowing down, so slowly decrease PWM, will work with brake()

#endif