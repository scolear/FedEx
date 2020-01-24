#include <iostream>
#include <QApplication>
#include "UiMainWindow.h"

int main(int argc, char** argv) {

    QApplication app(argc, argv);
    MainWindow win;
    win.show();
    return QApplication::exec();

    std::cout << "Hello, World!" << std::endl;
    return 0;
}
