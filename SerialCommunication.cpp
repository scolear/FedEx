#ifdef _WIN32
#include "SerialCommunication.h"
 
SerialCommunication::SerialCommunication(std::string portName, int baudrate) {

    open(portName);
    setUpSerialParams(baudrate);
    setUpSerialTimeouts();
}

SerialCommunication::~SerialCommunication() {
    close();
}

void SerialCommunication::open(std::string portName)
{
    _communicationHandle = CreateFile(portName.c_str(),                         // port name
                           GENERIC_READ | GENERIC_WRITE,                        // type of connection
                           0,
                           0,
                           OPEN_EXISTING,
                           0,
                           0);
    if (_communicationHandle == INVALID_HANDLE_VALUE) {
        if (GetLastError() == ERROR_FILE_NOT_FOUND) {
            std::cout << GetLastError() << std::endl;
        }
    }

    DCB serialParams = { 0 };
    serialParams.DCBlength = sizeof(serialParams);
    if (!GetCommState(_communicationHandle, &serialParams)) {
        std::cout << "Getcommstate error" << std::endl;
    }

    SetCommMask(_communicationHandle, EV_RXCHAR);
    if(EscapeCommFunction(_communicationHandle, CLRDTR) == 0) printf("Error Clearing DTR\n");
    
}

void SerialCommunication::setUpSerialParams(int baudrate)
{
    _communicationParams.BaudRate = baudrate;                               // Setting BaudRate
    _communicationParams.ByteSize = 8;                                      // Setting ByteSize = 8
    _communicationParams.StopBits = 1;                                      // Setting StopBits = 1
    _communicationParams.Parity = NOPARITY;                                 // Setting Parity = None
    SetCommState(_communicationHandle, &_communicationParams);
}

void SerialCommunication::send(const char* outgoingPacket, int size)
{
    DWORD dNoOFBytestoWrite = size;                                         // No of bytes to write into the port
    DWORD dNoOfBytesWritten = 0;                                            // No of bytes written to the port

    if (!WriteFile(_communicationHandle,                                    // Handle to the Serial port
        outgoingPacket,                                          // Data to be written to the port
        dNoOFBytestoWrite,                                       // No of bytes to write
        &dNoOfBytesWritten,                                      // Bytes written
        NULL)) {
        std::cout << "Write File Error" << std::endl;
    }
}

void SerialCommunication::read(char* incomingPacketAngle, char* incomingPacketDistance, int size)
{
    WaitCommEvent(_communicationHandle, &_dwEventMask, NULL);
    char* temp = (char*)calloc(1, sizeof(char));
    int last = 0;
    int otherLast = 0;
    uint32_t value = 0;
    bool startFlag = false;
    bool switchFlag = false;
    char start = 'n';
    char change = 'k';
    char stop = 'l';
    char delimer = ' ';
    while (last < size) {
            DWORD nRead = 0;
            if (!ReadFile(_communicationHandle,                                        // Handle to the Serial port          
                temp,                                                                  // buffer read into
                1,                                                                     // No of bytes to read
                &nRead,                                                                // Bytes read
                NULL)) {
                std::cout << "Read File Error" << std::endl;
            } 
            if (*temp == change) {
                switchFlag = true;
            }
            if (*temp == stop) {
                free(temp);
                return;
            }
            if (startFlag == true && switchFlag == false && !(*temp == change) && !(*temp == delimer)) {
                incomingPacketAngle[last] = *temp;
                last++;
            }
            if (switchFlag == true && !(*temp == change) && !(*temp == delimer)) {
                incomingPacketDistance[otherLast] = *temp;
                otherLast++;
            }
            if (*temp == start) {
                startFlag = true;
            }
    }
    free(temp);
}

void SerialCommunication::close()
{
    CloseHandle(_communicationHandle);
}

void SerialCommunication::setUpSerialTimeouts()
{
    _communicationTimeouts.ReadIntervalTimeout =            50;                         // in milliseconds
    _communicationTimeouts.ReadTotalTimeoutConstant =       50;                   // in milliseconds
    _communicationTimeouts.ReadTotalTimeoutMultiplier =     50;                  // in milliseconds
    _communicationTimeouts.WriteTotalTimeoutConstant =      50;                  // in milliseconds
    _communicationTimeouts.WriteTotalTimeoutMultiplier =    50;                 // in milliseconds

    if (!SetCommTimeouts(_communicationHandle, &_communicationTimeouts)) {
        std::cout << "Timeout set problem" << std::endl;
    }
}
#endif
 