#ifdef _WIN32
#pragma once
#include <windows.h>
#include <string>
#include <stdio.h>
#include <iostream>
#include <vector>

class SerialCommunication {
public:
    SerialCommunication(std::string, int);
    ~SerialCommunication();
    void open(std::string portName);
    void send(const char* outgoingPacket, int size);
    void read(char* incomingPacketAngle, char* incomingPacketDistance, int size);
    void close();
private:
    void setUpSerialParams(int);
    void setUpSerialTimeouts();
    HANDLE _communicationHandle;
    DCB _communicationParams;
    COMMTIMEOUTS _communicationTimeouts;
    DWORD _dwEventMask;
};
#endif