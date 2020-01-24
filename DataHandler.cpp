#include <iostream>
#include "DataHandler.h"
#include <QMetaType>

DataHandler::DataHandler()
{
    qRegisterMetaType<std::map<int, int>>("Type");

    auto* reader = new Reader;
    reader->moveToThread(&_readerThread);

    QObject::connect(&_readerThread, &QThread::finished, reader, &QObject::deleteLater);
    QObject::connect(this, &DataHandler::startReading, reader, &Reader::readData);
    QObject::connect(reader, SIGNAL(dataReady(Type)), this, SLOT(handleResults(Type)));
    _readerThread.start();
}

DataHandler::~DataHandler()
{
    _readerThread.quit();
    _readerThread.wait();
}

void DataHandler::handleResults(const std::map<int, int>& data)
{
    for (auto dat : data) {
        std::cout << dat.first << " : " << dat.second << std::endl;
    }
}