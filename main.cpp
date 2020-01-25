#include <iostream>
#include <QApplication>
#include "UiMainWindow.h"
#include "DataToMat.h"
#include "DataHandler.h"
#include "SerialCommunication.h"


int main(int argc, char** argv)
{
    QApplication app(argc, argv);
    MainWindow win;
    win.show();

    DataHandler handler("/dev/ttyACM0", win);

    handler.startReading();

    return QApplication::exec();

}
