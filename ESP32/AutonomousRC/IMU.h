#ifndef IMU_H
#define IMU_H

#include <Wire.h>
#include <Arduino.h>

#define SDA_PIN 26
#define SCL_PIN 27

struct IMU_DATA{
  int16_t accel_x; 
  int16_t accel_y;
  int16_t accel_z;
  int16_t temp;
  int16_t gyro_x;
  int16_t gyro_y;
  int16_t gyro_z;
};

class IMU{
  public:
    IMU();
    void begin();
    void update();
    void fillData();
    IMU_DATA getData() const;

  private:
    IMU_DATA data;
};

#endif