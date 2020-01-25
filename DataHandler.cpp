#include <iostream>
#include "DataHandler.h"
#include <QMetaType>

DataHandler::DataHandler(std::string comPort, MainWindow& mainWindow) : _mainWindow(mainWindow), _dataverter(600)
{
    qRegisterMetaType<std::map<int, int>>("Type");

    // reader object is moved to another thread. From there, it signals with dataReady() to the handler's handleResults();
    auto* reader = new Reader(comPort, &_data);

    reader->moveToThread(&_readerThread);

    QObject::connect(&_readerThread, &QThread::finished, reader, &QObject::deleteLater);
    QObject::connect(this, SIGNAL(startReading()), reader, SLOT(readData()));
    QObject::connect(reader, SIGNAL(dataReady()), this, SLOT(handleResults()));
    _readerThread.start();
}

DataHandler::~DataHandler()
{
    _readerThread.quit();
    _readerThread.wait();
}

void DataHandler::handleResults()
{
    for (auto dat : _data) {
        std::cout << dat.first << " : " << dat.second << " distance / 3: " << (dat.second / 3) << std::endl;
        *_mainWindow.getImage() = _dataverter.convert(_mainWindow.getImage(), dat.first, (dat.second) / 3);
    }
    handleMat();
}

std::map<int, int>& DataHandler::getMap()
{
    return _data;
}

void DataHandler::handleMat()
{
    _mainWindow.setFrame();
}
