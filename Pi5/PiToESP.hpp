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
    int8_t start;
    int8_t throttle;
    int8_t brake;
    int8_t steering;
    int8_t checksum;
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
