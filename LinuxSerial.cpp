#if defined(__unix__) || defined(__APPLE__)

#include <cstring>
#include <utility>
#include <sys/time.h>
#include "LinuxSerial.h"

SerialCommunication::SerialCommunication(std::string portName, int baudRate) : UARTConnection(std::move(portName), baudRate)
{
    open();
}

SerialCommunication::~SerialCommunication()
{
    close();
}

void SerialCommunication::open()
{
    _serialPortDescriptor = ::open(_portName.c_str(), O_RDWR | O_NOCTTY | O_NDELAY);

    if (_serialPortDescriptor < 0) {
        printf("Error %i from open: %s\n", errno, strerror(errno));
    }
    setupStruct();
}

void SerialCommunication::setupStruct()
{
    fcntl(_serialPortDescriptor, F_SETFL, FNDELAY);

    if (tcgetattr(_serialPortDescriptor, &_tty) != 0) {
        printf("Error %i from tcgetattr: %s\n", errno, strerror(errno));
    }
    memset(&_tty, 0, sizeof(_tty));

// Set in/out baud rate
    speed_t speed;
    switch (_baudRate)
    {
        case 110  :     speed = B110; break;
        case 300  :     speed = B300; break;
        case 600  :     speed = B600; break;
        case 1200 :     speed = B1200; break;
        case 2400 :     speed = B2400; break;
        case 4800 :     speed = B4800; break;
        case 9600 :     speed = B9600; break;
        case 19200 :    speed = B19200; break;
        case 38400 :    speed = B38400; break;
        case 57600 :    speed = B57600; break;
        case 115200 :   speed = B115200; break;
        default :       speed = _baudRate; break;
    }

    cfsetispeed(&_tty, speed);
    cfsetospeed(&_tty, speed);

    _tty.c_cflag |= ( CLOCAL | CREAD |  CS8);
    _tty.c_iflag |= ( IGNPAR | IGNBRK );

    _tty.c_cc[VTIME] = 0;          // Wait for up to 1s (10 deciseconds), returning as soon as any data is received.
    _tty.c_cc[VMIN] = 0;

// Save _tty settings, also checking for error
    if (tcsetattr(_serialPortDescriptor, TCSANOW, &_tty) != 0) {
        printf("Error %i from tcsetattr: %s\n", errno, strerror(errno));
    }
}

void SerialCommunication::send(const char *outgoingPacket, int size)
{
    int n = ::write(_serialPortDescriptor, outgoingPacket, size);
    printf("elements written: %d\n", n);
}

char SerialCommunication::readChar(char *pByte, unsigned int timeOutMS)
{
    TimeOut timer;
    timer.initTimer();

    while (timer.elapsedTimeMS() < timeOutMS || timeOutMS == 0)
    {
        // Try to read a byte on the device
        switch (::read(_serialPortDescriptor, pByte, 1)) {
            case 1  : return 1;
            case -1 : return -2;
        }
    }
    return 0;
}

void SerialCommunication::read(char *incomingPacket, int size)
{
    memset(incomingPacket, '\0', size);
    readString(incomingPacket, '\n', size, 20);
}

void SerialCommunication::close()
{
    ::close(_serialPortDescriptor);
}

int SerialCommunication::readStringNoTimeOut(char *receivedString, char finalChar, unsigned int maxNbBytes)
{
    // Number of characters read
    unsigned int    NbBytes = 0;
    // Returned value from Read
    char            charRead;

    // While the buffer is not full
    while (NbBytes < maxNbBytes)
    {
        // Read a character with the restant time
        charRead = readChar(&receivedString[NbBytes]);

        // Check a character has been read
        if (charRead == 1)
        {
            // Check if this is the final char
            if (receivedString[NbBytes] == finalChar)
            {
                // This is the final char, add zero (end of string)
                receivedString[++NbBytes] = 0;
                // Return the number of bytes read
                return NbBytes;
            }

            // The character is not the final char, increase the number of bytes read
            NbBytes++;
        }

        // An error occured while reading, return the error number
        if (charRead < 0) return charRead;
    }
    // Buffer is full : return -3
    return -3;
}

int SerialCommunication::readString(char *receivedString, char finalChar, unsigned int maxNbBytes, unsigned int timeOutMS)
{
    // Check if timeout is requested
    if (timeOutMS == 0) return readStringNoTimeOut(receivedString, finalChar, maxNbBytes);

    // Number of bytes read
    unsigned int    nbBytes = 0;
    // Character read on serial device
    char            charRead;
    // Timer used for timeout
    TimeOut         timer;
    long int        timeOutParam;

    // Initialize the timer (for timeout)
    timer.initTimer();

    // While the buffer is not full
    while (nbBytes < maxNbBytes)
    {
        // Compute the TimeOut for the next call of ReadChar
        timeOutParam = timeOutMS - timer.elapsedTimeMS();

        // If there is time remaining
        if (timeOutParam > 0)
        {
            // Wait for a byte on the serial link with the remaining time as timeout
            charRead = readChar(&receivedString[nbBytes], timeOutParam);

            // If a byte has been received
            if (charRead == 1)
            {
                // Check if the character received is the final one
                if (receivedString[nbBytes] == finalChar)
                {
                    // Final character: add the end character 0
                    receivedString[++nbBytes] = 0;
                    // Return the number of bytes read
                    return nbBytes;
                }
                // This is not the final character, just increase the number of bytes read
                nbBytes++;
            }
            // Check if an error occured during reading char
            // If an error occurend, return the error number
            if (charRead < 0) return charRead;
        }
        // Check if timeout is reached
        if (timer.elapsedTimeMS() > timeOutMS)
        {
            // Add the end caracter
            receivedString[nbBytes] = 0;
            // Return 0 (timeout reached)
            return 0;
        }
    }

    // Buffer is full : return -3
    return -3;
}


SerialCommunication::TimeOut::TimeOut() {}

void SerialCommunication::TimeOut::initTimer()
{
    gettimeofday(&_previousTime, nullptr);
}

unsigned long int SerialCommunication::TimeOut::elapsedTimeMS()
{
    // Current time
    struct timeval currentTime;
    // Number of seconds and microseconds since last call
    long sec, usec;

    // Get current time
    gettimeofday(&currentTime, nullptr);

    // Compute the number of seconds and microseconds elapsed since last call
    sec = currentTime.tv_sec - _previousTime.tv_sec;
    usec = currentTime.tv_usec - _previousTime.tv_usec;

    // If the previous usec is higher than the current one
    if (usec < 0)
    {
        // Recompute the microseonds and substract one second
        usec = 1000000 - _previousTime.tv_usec + currentTime.tv_usec;
        sec--;
    }

    // Return the elapsed time in milliseconds
    return sec * 1000 + usec / 1000;
}
#endif