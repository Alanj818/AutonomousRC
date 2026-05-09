#include "Lidar.h"
#include <Arduino.h>

//Not sure yet, Lidar functionallity/data parsing

Lidar::Lidar(int id){
  id = LidarId; 
}

void Lidar::begin(){
  //intialize lidar 
  Serial.println("Lidar Begin Simulation"); 
}

void Lidar::update(){
  //update values, consider interrupts and data sharing 
  Serial.println("Lidar data updated Simulation"); 
}

int Lidar::getDistance() const{
  Serial.println("Lidar Distance Simulated");
  return distance;
}