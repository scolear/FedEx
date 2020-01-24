#include "DataConverter.h"

DataConverter::DataConverter(std::map<int, int>& datamap, MainWindow& mainWindow) : _dataMap(datamap), _mainWindow(mainWindow) {}

void DataConverter::convertData()
{
    DataToMat dataverter(600);
    cv::Mat* temp = _mainWindow.getImage();

    while(true) {

        for (auto data : _dataMap) {
            *temp = dataverter.convert(temp, data.first, data.second);
            emit matReady();
        }
    }
}