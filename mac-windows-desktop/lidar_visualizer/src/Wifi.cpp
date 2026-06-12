#include "Wifi.hpp"

Wifi::Wifi() : sock(-1), distance(0) {}

void Wifi::begin(){
    sock = socket(AF_INET, SOCK_DGRAM, 0);
    addr.sin_port = htons(9000);
    addr.sin_addr.s_addr = INADDR_ANY;
    addr.sin_family = AF_INET;
    
    size_addr = sizeof(addr);

    if(sock < 0){
        std::cerr << "Socket initialization error"; 
        return;
    }

    int flags = fcntl(sock, F_GETFL, 0);
    fcntl(sock, F_SETFL, flags | O_NONBLOCK);
}

void Wifi::startCon(){
    if(sock < 0){
        std::cerr << "Socket not initialized for binding.";
    } else {
        if(bind(sock, (sockaddr *)&addr, size_addr) < 0){
            std::cerr << "Binding error, check port availablility";
            return;
        } else {
            std::cout << "Successfully Bound to port 9000" << std::endl;
        }
    }
}

void Wifi::udp_listen(){
    if(sock < 0){
        std::cerr << "Socket not initialized for listening.";
        return;
    } 
        while(true){
            size_saddr = sizeof(saddr);
            int recvfrom_int = recvfrom(sock, buffer, sizeof(buffer), 0, (sockaddr *)&saddr, &size_saddr);
            if(recvfrom_int < 0){
                if(errno == EAGAIN || errno == EWOULDBLOCK){
                    return;
                }
                std::cerr << "UDP error.";
                return;
            }
            
            if(recvfrom_int == 2){
                //i got lazy i dont wanna change it but esp sends low then high, so switched them around 
                distance = decodePacketFromEsp(buffer[1], buffer[0]);
                std::cout << "Distance: " << distance << std::endl;
            }
        }
}

void Wifi::endCon(){
    close(sock);
}

uint16_t Wifi::decodePacketFromEsp(uint8_t high, uint8_t low){
    return (static_cast<uint16_t>(high) << 8 | low);
}

uint16_t Wifi::getDistance(){
    return distance;
}