#include "Wifi.h"

Wifi::Wifi() {}

WiFiUDP udp;
IPAddress broadcastIP(255,255,255,255); //broadcast to anyone on wifi, using private wifi/hotspot so should be fine

void Wifi::begin(){
    WiFi.disconnect();
    udp.stop();
    WiFi.begin(ssid, password);
    udp.begin(port);
    Serial.println("WiFi Begin Simulated");
    
}

void Wifi::sendData(uint16_t distance){
  if(WiFi.status() != WL_CONNECTED){
    return;
  }

  //distance of lidar is uint16_t but write expects uint8_t, so we send a buffer with Low and High byte of distance
  uint8_t byte[2];
  byte[0] = lowByte(distance);
  byte[1] = highByte(distance);

  udp.beginPacket(broadcastIP, port);
  udp.write(byte, 2);
  udp.endPacket();
}


void Wifi::update(){
  static bool printedConnect = false;
  // Lets just print broadcast and port
  if(WiFi.status() == WL_CONNECTED){
    if(!printedConnect){
      Serial.print("WiFi Connected!\n");
      Serial.printf("WiFi Broadcasting to %u.%u.%u.%u at port %d\n", broadcastIP[0], broadcastIP[1], broadcastIP[2], broadcastIP[3], port);
      printedConnect = true;
    } 
  } else {
      if(printedConnect){
        Serial.print("Not Connected. \n");
        printedConnect = false;
      }
    }
}
