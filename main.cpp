#include <iostream>
#include "SerialCommunication.h"

int main() {
    SerialCommunication* serial = new SerialCommunication("\\\\.\\COM12", 115200);
    char recievedPacketAngle[10];
    char recievedPacketDistance[10];
    serial->send("s s\n", 5);
    serial->send("s s\n", 5);
    serial->send("s s\n", 5);
    serial->send("s s\n", 5);
    serial->send("s s\n", 5);
    serial->send("s s\n", 5);
    serial->send("s s\n", 5);
    serial->send("s s\n", 5);
    for (int i = 0; i < 10; i++) {
        recievedPacketAngle[i] = '\0';
        recievedPacketDistance[i] = '\0';
    }
    while (1) {
        serial->read(recievedPacketAngle, recievedPacketDistance,10);
        std::cout << "angle:";
        printf("%s", recievedPacketAngle);
        std::cout << "distance:";
        printf("%s", recievedPacketDistance);
        std::cout << std::endl;
        for (int i = 0; i < 10; i++) {
            recievedPacketAngle[i] = '\0';
        }
        for (int i = 0; i < 10; i++) {
            recievedPacketDistance[i] = '\0';
        }
    }
    return 0;
}
