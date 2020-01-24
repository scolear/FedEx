
#include "Reader.h"

Reader::Reader(std::map<int, int>* datamap) : data(datamap) {}

void Reader::readData()
{
    for (int i = 0; i < 100; ++i) {

        //data->insert(std::make_pair(rand() % 360, (rand() % 1000)));

        (*data)[(rand() % 360)] = (rand() % 1000);

        QThread::sleep(1);

        if (i == 6) {
            emit dataReady();
            i = 0;
        }
    }
}