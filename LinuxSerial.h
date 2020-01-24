#if defined(__unix__) || defined(__APPLE__)

#ifndef CHAMA_FUCHSITE_LINUXSERIAL_H
#define CHAMA_FUCHSITE_LINUXSERIAL_H

#include <fcntl.h>      // Contains file controls like O_RDWR
#include <cerrno>       // Error integer and strerror() function
#include <termios.h>    // Contains POSIX terminal control definitions
#include <unistd.h>     // write(), read(), close()
#include <string>

class SerialCommunication {
public:
    SerialCommunication(std::string portName, int baudRate);
    ~SerialCommunication();
    void open();
    void send(const char *outgoingPacket, int size);
    void read(char* incomingPacketAngle, char* incomingPacketDistance, int size);
    void close() ;

private:
    void setupStruct();
    char readChar(char *pByte, unsigned int timeOut_ms=0);
    int  readString(char *receivedString, char finalChar, unsigned int maxNbBytes, unsigned int timeOut_ms=0);
    int  readStringNoTimeOut(char *receivedString,char finalChar,unsigned int maxNbBytes);

    struct termios _tty;
    int            _serialPortDescriptor;

    std::string _portName;
    int _baudRate;

    class TimeOut {
    public:
        TimeOut();
        void initTimer();
        unsigned long int   elapsedTimeMS();
    private:
        struct timeval      _previousTime;
    };
};


#endif //CHAMA_FUCHSITE_LINUXSERIAL_H

#endif //unix
