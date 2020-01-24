#ifndef FEDEX_DATAHANDLER_H
#define FEDEX_DATAHANDLER_H


#include <QtCore/QObject>
#include <QtCore/QThread>
#include "Reader.h"

class DataHandler : public QObject
{
    Q_OBJECT

    QThread _readerThread;

public:
    DataHandler(std::string);
    ~DataHandler();

public slots:
    void handleResults(const std::map<int, int>&);
signals:
    void startReading();

};


#endif //FEDEX_DATAHANDLER_H
