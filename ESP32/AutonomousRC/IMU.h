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

struct IMU_CONVERTED_DATA{
  float accel_x;
  float accel_y;
  float accel_z;
  float temp;
  float gyro_x;
  float gyro_y;
  float gyro_z;
};

class IMU{
  public:
    IMU();
    void begin();
    void update();
    void fillData();
    IMU_DATA getData() const;
    void handleDataConversion();

  private:
    IMU_DATA data;
    IMU_CONVERTED_DATA data_converted;
};

#endif