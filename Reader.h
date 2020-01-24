#ifndef FEDEX_READER_H
#define FEDEX_READER_H

#include <QtCore/QObject>
#include <QtCore/QThread>
#include "SerialCommunication.h"
#include <memory>
#include <string>

class Reader : public QObject
{
    Q_OBJECT

public:
    Reader(std::string);

public slots:
    void readData();

signals:
    void dataReady(const std::map<int, int> angleDistanceData);

private:
    std::map<int, int> _data;
    std::unique_ptr<SerialCommunication> _communication;
};


#endif //FEDEX_READER_H
