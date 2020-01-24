#include <iostream>
#include "DataHandler.h"
#include <QMetaType>

DataHandler::DataHandler(std::string comPort)
{
    qRegisterMetaType<std::map<int, int>>("Type");

    // reader object is moved to another thread. From there, it signals with dataReady() to the handler's handleResults();
    auto* reader = new Reader(comPort, &_data);

    reader->moveToThread(&_readerThread);

    QObject::connect(&_readerThread, &QThread::finished, reader, &QObject::deleteLater);
    QObject::connect(this, SIGNAL(startReading()), reader, SLOT(readData()));
    QObject::connect(reader, SIGNAL(dataReady()), this, SLOT(handleResults()));
    _readerThread.start();

    auto* converter = new DataConverter(_data);

    converter->moveToThread(&_converterThread);

    QObject::connect(&_converterThread, &QThread::finished, converter, &QObject::deleteLater);
    QObject::connect(this, SIGNAL(startConverting()), converter, SLOT(convertData()));
    QObject::connect(converter, SIGNAL(matReady()), this, SLOT(handleMat()));
    _converterThread.start();

}

DataHandler::~DataHandler()
{
    _readerThread.quit();
    _readerThread.wait();
    _converterThread.quit();
    _converterThread.wait();
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

void DataHandler::handleMat()
{

}
