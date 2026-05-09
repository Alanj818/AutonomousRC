#ifndef BAT_H
#define BAT_H

#define BAT_PIN some_pin

float batADC(float raw); //gets adc reading for bat 0-4095 12 bit 
int batPercent(float adc); //gets percentage of battery life
int batVoltage(float adc); //gets voltage reading from adc value
#endif
