#include <iostream>
#include <QApplication>
#include "UiMainWindow.h"
#include "DataToMat.h"
#include "DataHandler.h"

int main(int argc, char** argv)
{
    std::srand(time(nullptr));

    QApplication app(argc, argv);
    MainWindow win;
    win.show();

    int width = 600;
    DataToMat dataverter(width);
    std::vector<float> data;
    for (size_t i = 0; i < 360; i++)
    {
        data.push_back((rand() % (width/2)) +5);
    }

    DataHandler handler;

    handler.startReading();

    return QApplication::exec();
}
