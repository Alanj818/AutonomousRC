#include "PiToESP.hpp"
PiToESP::PiToESP(){
    
}

void PiToESP::begin(const std::string& ch, int baud){
    //initialize uart here
    if((fd = open(ch.c_str(), O_RDWR | O_NOCTTY)) == -1){
        perror("open");
        exit(EXIT_FAILURE);
    }
    
    if((tcgetattr(fd, &tty)) == -1){
        perror("tcgetattr");
        exit(EXIT_FAILURE);
    }
    //modify tty to what i want then
    /*
     BAUD RATE change really
     Data Bits
     Parity Bits
     Stop Bits
     Echoing
     Non Canonical mode
     */
    if(baud == 115200){
        cfsetispeed(&tty, B115200); //sets input baud
        cfsetospeed(&tty, B115200); //sets output baud
    } else {
        cfsetispeed(&tty, B9600);
        cfsetospeed(&tty, B9600);
    }
    
    tty.c_lflag &= ~ECHO; //disables echo
    tty.c_lflag &= ~ICANON; //disables canonical mode, not talking to terminal
    tty.c_lflag &= ~ISIG;
    tty.c_lflag &= ~IEXTEN;
    
    tty.c_cflag &= ~PARENB; //disables parity
    tty.c_cflag &= ~CSIZE; //clears data size
    tty.c_cflag |= CS8; //sets size to 8 bits
    tty.c_cflag |= CREAD;
    tty.c_cflag |= CLOCAL;
    tty.c_cflag &= ~CSTOPB; //set stop bit to false for 1 bit
    
    tty.c_iflag &= ~IXON;
    tty.c_iflag &= ~IXOFF;
    tty.c_iflag &= ~IXANY;
    tty.c_iflag &= ~ICRNL;
    tty.c_iflag &= ~INLCR;
    tty.c_iflag &= ~IGNCR;
    
    tty.c_oflag &= ~OPOST;
    
    tty.c_cc[VMIN] = 0;
    tty.c_cc[VTIME] = 0;
    
    //this allows for BAUD B115200, SERIAL_8N1
    
    if((tcsetattr(fd,TCSANOW, &tty)) == -1){
        perror("tcsetattr");
        exit(EXIT_FAILURE);
    }
}

void PiToESP::sendPackets(/*void* buffer*/){
    //this is just to make sure UART0 Works so inputting default values for now
    uart.start = 0xAA;
    uart.throttle = 5;
    uart.brake = 0;
    uart.steering = 5;
    uart.checksum = uart.start ^ uart.brake ^ uart.throttle ^ uart.steering;
    ssize_t n = write(fd, &uart, sizeof(uart));

    if(n != sizeof(uart)){
        perror("write");
    }
}

LIDAR PiToESP::receivePackets(/*void* buffer*/){
    uint8_t buffer[9];
    ssize_t n = read(fd, buffer, sizeof(buffer));

    //start of state machine
    static int state = 0; 
    static int idx = 0;

    if(n < 0){
        //there will be a lidar.error = some enum lidar error 
        lidar.error = LidarError::Error;
        return lidar;
    } else if(n == 0){
        //there will be a lidar.error = some enum lidar no bytes error
        lidar.error = LidarError::NoBytes;
        return lidar;
    } else if(n > 0){
        //there were bytes do the checksum and all
        for(ssize_t i = 0; i < n; i++){
            uint8_t byte = buffer[i];

            if(state == 0 && byte == 0x59){
                //if were at state 0 and see a 0x59, add it and go to state 1
                packet[idx++] = byte;
                state = 1;
            } else if(state == 1){
                //if were at state 1 and see a 0x59, add it and then go to state 2
                if(byte == 0x59){
                    packet[idx++] = byte;
                    state = 2;
                } else {
                    state = 0; 
                    idx = 0;
                }
            } else if(state == 2){
                //if were at state 2, then we met all conditions to fill up the rest of the packet and do a checksum
                packet[idx++] = byte;
                if(idx == 9){
                    //checksum here
                    uint8_t checksum = 0;
                    for(int i = 0; i < 8; i++){
                        checksum += packet[i];
                    }
                    if(checksum != packet[8]){
                        idx = 0;
                        state = 0;
                        lidar.error = LidarError::Checksum;
                        return lidar;
                    } else {
                        idx = 0;
                        state = 0;
                        uint8_t lowD = packet[2];
                        uint8_t highD = packet[3];
                        lidar.distance = lowD | (highD << 8);
                        lidar.error = LidarError::NoError;
                        return lidar;
                    }

                }
            }

        }
        //there will be an error for non matching 0x59s in the first 2 bytes and return
        //there will be an error for incorrect checksum and return

    }
    //here if all went right, lidar.error = some enum lidar no error value
    lidar.error = LidarError::Incomplete;
    return lidar;
}

void PiToESP::end(){
    if(fd != -1){
        close(fd);
        fd = -1;
    }
}
