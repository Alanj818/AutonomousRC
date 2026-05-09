#include "Battery.h"
#include <Arduino.h> 

//handles battery readings 

float batADC(float raw){
  float adcValue = 0.0; //here we will do calculations for the battery
  return adcValue; 
}

int batPercent(float adc){
  int percent = 0;//Here we will calculate the percentage of the battery 

  return percent; 
}

int batVoltage(float adc){
  int voltage = 0; //here we will revert adc to voltage
  return voltage; 
}