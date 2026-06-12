#ifndef WIFI_H
#define WIFI_H

#include <WiFiUdp.h>
#include <WiFi.h>

class Wifi{
  public: 
    Wifi();
    void begin();
    void update();
    void sendData(uint16_t distance);


  private: 
    int port = 9000;
    const char* ssid = "casa1338"; 
    const char* password = "tealdesk328";
};

#endif