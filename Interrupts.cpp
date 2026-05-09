#include "Interrupts.h"
#include <Arduino.h> 

//Hanles interrupts service here, ISR 
volatile bool mFlag = false; 
volatile bool sFlag = false; 
volatile bool lFlag = false; 

//ISR SHOULD ONLY DO DATA UPDATING OR FLAG SETTING, NOTHING ELSE THAT MAY SLOW IT DOWN
void mISR_Function(){
  mFlag = true;
}

void sISR_Function(){
  sFlag = true; 
}

void lISR_Function(){
  lFlag = true;
}