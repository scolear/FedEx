#include <iostream>
#include "DataHandler.h"
#include <QMetaType>

DataHandler::DataHandler()
{
    qRegisterMetaType<std::map<int, int>>("Type");

    // reader object is moved to another thread. From there, it signals with dataReady() to the handler's handleResults();
    auto* reader = new Reader(&_data);
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
        std::cout << dat.first << " : " << dat.second << std::endl;
    }
}

std::map<int, int>& DataHandler::getMap()
{
    return _data;
}