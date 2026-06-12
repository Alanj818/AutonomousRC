#ifndef WIFI_H
#define WIFI_H

#include <sys/socket.h>
#include <sys/uio.h>
#include <unistd.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h> 
#include <iostream>
#include <cstring>
#include <fcntl.h>
#include <cerrno>

class Wifi{
    public:
        Wifi();
        void begin();
        void startCon(); 
        void udp_listen();
        void endCon();
        uint16_t decodePacketFromEsp(uint8_t high, uint8_t low);
        uint16_t getDistance();

    private:
        sockaddr_in addr{};
        sockaddr_in saddr{};
        int sock = -1;
        uint8_t buffer[256];
        socklen_t size_addr = 0;
        socklen_t size_saddr = 0;
        uint16_t distance = 0;
};

#endif