#include "piCommands.h"
#include <Arduino.h>

piCommands::piCommands() : pi(2) {}


void piCommands::begin(){
  pi.begin(115200, SERIAL_8N1, PI_PIN, -1);
  Serial.println("PI COMMANDS INITIALIZED");
}

void piCommands::getCommands(){
  //we will implement a state machine: 0, 1 , 2. 0 for the start byte, 2 to fill up the rest of the buffer, 3 compute checksum to make sure all data is there 
  static int state = 0;
  static int idx = 0;
  uint8_t checksum = 0;

  while(pi.available() > 0){
    auto p = pi.read();
    Serial.printf("First Byte: %02X\n", (uint8_t)p);
    if(p < 0){
      break;
    }
    //check first byte
    if(state == 0){
      bits[0] = p;
      if(p == 0xAA){
        state = 1;
        idx = 1;
        Serial.printf("Passed State 0");
      }
    } else if (state == 1){
      //fill up buffer here
        bits[idx++] = p;

        if(idx == 5){
          checksum = bits[0] ^ bits[1] ^ bits[2] ^ bits[3];
          Serial.printf("YOU REACHED CHECKSUM");
          
          if(checksum == bits[4]){
            throttle = static_cast<int8_t>(bits[1]);
            brake = static_cast<int8_t>(bits[2]);
            steering = static_cast<int8_t>(bits[3]);
          }
          state = 0;
          idx = 0;
        }
    }
  }
}

void piCommands::update(){
  Serial.printf("Throttle: %d", throttle);
  Serial.println();
  Serial.printf("Brake: %d", brake);
  Serial.println();
  Serial.printf("Steering: %d", steering);
}
