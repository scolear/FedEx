#ifndef FEDEX_DATAHANDLER_H
#define FEDEX_DATAHANDLER_H


#include <QtCore/QObject>
#include <QtCore/QThread>
#include "Reader.h"
#include "DataConverter.h"

class DataHandler : public QObject
{
    Q_OBJECT

    QThread _readerThread;
    QThread _converterThread;

public:
    explicit DataHandler(std::string);
    ~DataHandler() override;

    std::map<int, int>& getMap();

public slots:
    void handleResults();
    void handleMat();
signals:
    void startReading();
    void startConverting();

private:
    std::map<int, int> _data;

};


#endif //FEDEX_DATAHANDLER_H
