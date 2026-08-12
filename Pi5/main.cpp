#include <iostream>
#include "PiToESP.hpp"
#include <chrono>

//Create a constant loop for this

using Clock = std::chrono::steady_clock;

int main(){
    PiToESP pi;
    PiToESP lidar;
    LIDAR lidar_packet;
    pi.begin("/dev/serial0", 115200); //uart0 /dev/ttyAMA10
    lidar.begin("/dev/ttyAMA2", 115200); //uart2 /dev/ttyAMA2 PINS GPIO4(TX) GPIO5(RX)
    
    auto lastTime = Clock::now();
    for(;;){
        auto now = Clock::now();
        if(now - lastTime >= std::chrono::milliseconds(20)){
            lastTime = now;
            //pi.sendPackets();
            lidar_packet = pi.receivePackets();
            //lidar.sendPackets();
            lidar_packet = lidar.receivePackets();
            std::cout << "UART0: "<< lidar_packet.distance << "\n" << std::endl;
        }
        
    }
    pi.end();
    return 0;
}
