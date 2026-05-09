#ifndef SERVOS_H
#define SERVOS_H

#define SERVO_PIN some_pin

class Servos{
  public:
    Servos(int id);

    void steer(int x, int y); //using joystic for this, x coordinates matter most 
    void update();
    void begin();

  private: 
    int joyY; 
    int joyX; 
    int servosId; 
};
#endif