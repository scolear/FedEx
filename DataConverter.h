#ifndef FEDEX_DATACONVERTER_H
#define FEDEX_DATACONVERTER_H

#include <QtCore/QObject>
#include <QtCore/QThread>

#include "DataToMat.h"
#include "UiMainWindow.h"

class DataConverter : public QObject
{
    Q_OBJECT

public:
    DataConverter(std::map<int, int>& datamap, MainWindow& mainWindow);

public slots:
    void convertData();

signals:
    void matReady();

private:
    std::map<int, int>& _dataMap;
    MainWindow& _mainWindow;

};


#endif //FEDEX_DATACONVERTER_H
