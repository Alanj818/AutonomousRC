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

struct LIDAR{
    LidarError error = LidarError::NoError;
    uint16_t distance;
};

enum class LidarError{
    Error,
    NoBytes,
    NoError, 
    Checksum,
    Incomplete
};

class PiToESP {
public:
    PiToESP();
    void begin(const std::string& ch, int baud = 9600);
    void sendPackets(/*void* buffer*/);
    LIDAR receivePackets();
    void end();
    

private:
    UART uart;
    LIDAR lidar;//i dont think i need this to recieve.... i actually did lol 
    termios tty;
    int fd = -1;
    uint8_t packet[9];
};

#endif
