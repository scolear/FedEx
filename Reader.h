#ifndef FEDEX_READER_H
#define FEDEX_READER_H

#include <QtCore/QObject>
#include <QtCore/QThread>

class Reader : public QObject
{
    Q_OBJECT

public:
    Reader(std::map<int, int>* datamap);

public slots:
    void readData();

signals:
    void dataReady();

private:
    std::map<int, int>* data;

};


#endif //FEDEX_READER_H
