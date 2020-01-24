#ifndef FEDEX_READER_H
#define FEDEX_READER_H

#include <QtCore/QObject>
#include <QtCore/QThread>

class Reader : public QObject
{
    Q_OBJECT

public slots:
    void readData();

signals:
    void dataReady(const std::map<int, int> angleDistanceData);

private:
    std::map<int, int> _data;
};


#endif //FEDEX_READER_H
