#ifndef PI_H
#define PI_H
#include <iostream>
#include <termios.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <string>
#include <cstdlib>
#include <cstdio>
#include <cstdint>

struct UART{
    uint8_t start;
    uint8_t throttle;
    uint8_t brake;
    uint8_t steering;
    uint8_t checksum;
};

class PiToESP {
public:
    PiToESP();
    void begin(const std::string& ch, int baud = 9600);
    void sendPackets(/*void* buffer*/);
    void end();
    

private:
    UART uart;
    termios tty;
    int fd = -1;
};

#endif
