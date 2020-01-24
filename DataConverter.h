#ifndef FEDEX_DATACONVERTER_H
#define FEDEX_DATACONVERTER_H

#include <QtCore/QObject>
#include <QtCore/QThread>

class DataConverter : public QObject
{
    Q_OBJECT

public:
    explicit DataConverter(std::map<int, int>& datamap);

public slots:
    void convertData();

signals:
    void matReady();

private:
    std::map<int, int>& _dataMap;

};


#endif //FEDEX_DATACONVERTER_H
