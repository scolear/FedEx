
#include "Reader.h"

void Reader::readData()
{
    for (int i = 0; i < 100; ++i) {

        _data.insert(std::make_pair(rand() % 360, (rand() % 1000)));
        QThread::sleep(1);

        if (i == 6) {
            emit dataReady(_data);
            _data.clear();
            i = 0;
        }
    }
}