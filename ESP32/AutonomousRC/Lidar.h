//probably a lidar public class to create an instance have things like lidar1.read(), lidar2.read()... lidarN.read(), in case i have more than one
#ifndef LIDAR_H
#define LIDAR_H

#define LIDAR_PIN 33
#define LIDAR_BAUD 115200

#include <Arduino.h>

class Lidar{
  public:
    Lidar(int id);
    void begin(); 
    void update(); 
    uint16_t getDistance(); 
  
  private: 
    int LidarId; 
    uint16_t distance; //default value will be in cm 
    HardwareSerial lidar;
    
    //gonna use a buffer called bits for UART bytes and checksum to verify UART packets are not corrupted. 
    uint8_t bits[9];
    uint8_t checksum = 0;
};
#endif