#ifndef CHAMA_FUCHSITE_UARTCONNECTION_H
#define CHAMA_FUCHSITE_UARTCONNECTION_H
#include <vector>
#include <string>

class UARTConnection {
public:
    UARTConnection(std::string portName, int baudRate);
    ~UARTConnection();

protected:
    virtual void open() = 0;

    virtual void send(const char* outgoingPacket, int size) = 0;
    virtual void read(char* incomingPacket, int size) = 0;

    virtual void close() = 0;

protected:
    std::string _portName;
    int _baudRate;
};


#endif //CHAMA_FUCHSITE_UARTCONNECTION_H
