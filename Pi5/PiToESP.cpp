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
    tty.c_cc[VTIME] = 1;
    
    //this allows for BAUD B115200, SERIAL_8N1
    
    if((tcsetattr(fd,TCSANOW, &tty)) == -1){
        perror("tcsetattr");
        exit(EXIT_FAILURE);
    }
}

void PiToESP::sendPackets(/*void* buffer*/){
    //this is just to make sure UART0 Works so inputting default values for now
    uart.start = 0xAA;
    uart.brake = 0;
    uart.throttle = 5;
    uart.steering = 5;
    uart.checksum = uart.start ^ uart.brake ^ uart.throttle ^ uart.steering;
    ssize_t n = write(fd, &uart, sizeof(uart));

    if(n != sizeof(uart)){
        perror("write");
    }
}

void PiToESP::end(){
    if(fd != -1){
        close(fd);
        fd = -1;
    }
}
