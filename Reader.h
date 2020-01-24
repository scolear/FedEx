#ifndef FEDEX_READER_H
#define FEDEX_READER_H

#ifdef __linux__
#include "LinuxSerial.h"
#endif

#include <QtCore/QObject>
#include <QtCore/QThread>
#include "SerialCommunication.h"
#include <memory>
#include <string>

class Reader : public QObject
{
    Q_OBJECT

public:
    Reader(std::string, std::map<int, int>* datamap);

public slots:
    void readData();

signals:
    void dataReady();

private:
    std::map<int, int>* _data;

    std::unique_ptr<SerialCommunication> _communication;
};


#endif //FEDEX_READER_H
