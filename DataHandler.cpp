#include "DataHandler.h"

DataHandler::DataHandler(std::string comPort, MainWindow& mainWindow) : _mainWindow(mainWindow), _dataverter(600), _timer(this)
{
    qRegisterMetaType<std::map<int, int>>("Type");

    // reader object is moved to another thread. From there, it signals with dataReady() to the handler's handleResults();
    auto* reader = new Reader(comPort, &_data);

    reader->moveToThread(&_readerThread);

    QObject::connect(&_readerThread, &QThread::finished, reader, &QObject::deleteLater);
    QObject::connect(this, SIGNAL(startReading()), reader, SLOT(readData()));
    QObject::connect(reader, SIGNAL(dataReady()), this, SLOT(handleResults()));
    //QObject::connect(reader, SIGNAL(sendDataPair(int, int)), this, SLOT(handlePair(int, int)));
    _readerThread.start();

    _mainWindow.updateLog("Connection established, reading data...");

    QObject::connect(&_timer, SIGNAL(timeout()), this, SLOT(clearFrame()));
    _timer.start(5000);
}

DataHandler::~DataHandler()
{
    _readerThread.quit();
    _readerThread.wait();
}

void DataHandler::handleResults()
{
    for (auto dat : _data) {
        //std::cout << dat.first << " : " << dat.second << " || distance / 3: " << (dat.second / 3) << std::endl;
        _mainWindow.setImage(_dataverter.convert(_mainWindow.getImage(), dat.first, (dat.second) / 3));
    }
    _mainWindow.setFrame();
}

void DataHandler::handlePair(int angle, int dist)
{
    _mainWindow.setImage(_dataverter.convert(_mainWindow.getImage(), angle, dist / 3));
    _mainWindow.setFrame();
}

void DataHandler::clearFrame()
{
    _dataverter.clearScreen(_mainWindow.getImage());
}