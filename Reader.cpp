
#include "Reader.h"

#include <memory>

Reader::Reader(std::string comPort, std::map<int, int>* datamap) : _data(datamap)
{
    _communication = std::make_unique<SerialCommunication>(comPort, 115200);
    //start lidar communication
    for (int i = 0; i < 5; i++) {
        _communication->send("s s\n", 5);
    }
}

void Reader::readData()
{
    char recievedPacketAngle[10];
    char recievedPacketDistance[10];
    int counter = 0;
    char endOfChar = '\0';
    while (1) {
        std::string angle;
        std::string distance;
        _communication->read(recievedPacketAngle, recievedPacketDistance, 10);
        for (int i = 0; i < 10; i++) {
            if (recievedPacketAngle[i] != endOfChar) {
                angle.push_back(recievedPacketAngle[i]);
            }
            if (recievedPacketDistance[i] != endOfChar) {
                distance.push_back(recievedPacketDistance[i]);
            }
        }
        int angleN = std::stoi(angle);
        int distanceN = std::stoi(distance);

        (*_data)[angleN] = distanceN;

        for (int i = 0; i < 10; i++) {
            recievedPacketAngle[i] = '\0';
            recievedPacketDistance[i] = '\0';
        }
        counter++;
        if (counter == 10) {
            emit dataReady();
            counter = 0;
        }
    }
}