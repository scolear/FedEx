#include <iostream>
#include <QApplication>
#include "UiMainWindow.h"
#include "DataToMat.h"

int main(int argc, char** argv) {
    std::srand(time(NULL));

    QApplication app(argc, argv);
    MainWindow win;
    win.show();


    /*int width = 600;
    DataToMat dataverter(width);
    std::vector<float> data;
    for (size_t i = 0; i < 360; i++)
    {
        data.push_back((rand() % (width/2)) +5);
        //data.push_back(50);

    }*/
    //cv::imshow("test", dataverter.convert(data));
    //cv::waitKey(0);
    return QApplication::exec();
}
