#ifndef DESIGNERIQFMCA_H
#define DESIGNERIQFMCA_H

#include "DataToMat.h"

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include <QTimer>

class DataToMat;

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    MainWindow();
    ~MainWindow() override;
    void generateLayout();
    void retranslateUi(QMainWindow *MainWindow);
    void setFrame();

public slots:
    void updateLog(const std::string& message);

private:
    QVBoxLayout     *_verticalLayout;
    QVBoxLayout     *_verticalLayout_2;
    QHBoxLayout     *_horizontalLayout;
    QHBoxLayout     *_horizontalLayout_2;
    QWidget         *_centralWidget;

    QWidget         *_labelWidget;
    QLabel          *_displayLabel;

    QWidget         *_buttonsWidget;
    QPushButton     *_connectButton;
    QPushButton     *_disconnectButton;
    QPushButton     *_saveResultButton;

    QWidget         *_textLogWidget;
    QLabel          *_messageLog;

    cv::Mat         *_image;
    DataToMat       *_dataToMat;
    static std::vector<float> *_data;

    QTimer _timer;

};

#endif // DESIGNERIQFMCA_H

