#include "Lidar.h"
//Not sure yet, Lidar functionallity/data parsing
Lidar::Lidar(int id) : lidar(1), LidarId(id){}

void Lidar::begin(){
  //intialize lidar 
  lidar.begin(LIDAR_BAUD, SERIAL_8N1, LIDAR_PIN, -1);
  Serial.println("Lidar Begin Simulated");
}

void Lidar::update(){
  //print values 
  Serial.printf("Obstacle at %dcm", distance);
}

uint16_t Lidar::getDistance() {
  static int state = 0; 
  static int idx = 0;
  while(lidar.available() > 0){
    //implement a state machine 
    int r = lidar.read();
    if(r < 0){
      break; 
    }

    uint8_t b = static_cast<uint8_t>(r);

    //state 0, check if first byte is 0x59
    if(state == 0){
      if(b == 0x59){
        bits[0] = b; 
        state = 1;
      }
    }
    
    //state 1, check if second byte is 0x59
    else if (state == 1){
      if(b == 0x59){
        bits[1] = b;
        state = 2;
        idx = 2;
      } else {
        state = 0; // we reset here if the string of bits is off, so back to 0
      }
    } 

    //state 2, fill the rest of the buffer bits up
    else {
      bits[idx++] = b;
      uint8_t checksum = 0;
      if(idx == 9){
        for(int i = 0; i < 8; i++){
          checksum += bits[i];
        }

        if(checksum == bits[8]){
          uint16_t high_byte = static_cast<uint16_t>(bits[3]) << 8; 
          uint16_t low_byte = bits[2]; 

          distance = high_byte | low_byte;
        }
        state = 0;
        idx = 0;
      }
    }
  }
  return distance;
}