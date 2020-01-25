#include <iostream>
#include <QApplication>
#include "UiMainWindow.h"
#include "DataToMat.h"
#include "DataHandler.h"
#include "SerialCommunication.h"


int main(int argc, char** argv)
{
    //std::srand(time(nullptr));

    QApplication app(argc, argv);
    MainWindow win;
    win.show();
    //
    //int width = 600;
    //DataToMat dataverter(width);
    //std::vector<float> data;
    //for (size_t i = 0; i < 360; i++)
    //{
    //    data.push_back((rand() % (width/2)) +5);
    //}

    /*
    int width = 600;

    DataToMat dataverter(width);

    std::vector<float> data;

    while (cv::waitKey(27))

    {
        for (int i = 0; i < 360; i++)
        {
            int random = (rand() % (width / 2)+20);            
            cv::imshow("test", dataverter.convert(img, i, random));
            cv::waitKey(1);
        }
        //dataverter.dottedShow(img, data);
        //data.clear();
        img.release();

    }*/

    DataHandler handler("\\\\.\\COM9", win);

    handler.startReading();
    handler.startConverting();

    return QApplication::exec();

    /*
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
    */
}
