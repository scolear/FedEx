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

    std::map<int, int>& getMap();

public slots:
    void handleResults();
signals:
    void startReading();

private:
    std::map<int, int> _data;

};


#endif //FEDEX_DATAHANDLER_H
