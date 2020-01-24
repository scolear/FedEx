#include "UiMainWindow.h"
#include <iostream>
#include <utility>


MainWindow::MainWindow() : _timer(this)
{
    generateLayout();

    QMetaObject::connectSlotsByName(this);
}

MainWindow::~MainWindow() {}

void MainWindow::generateLayout()
{
    if (objectName().isEmpty())
        setObjectName(QString::fromUtf8("MainWindow"));
        resize(505, 383);
    _centralWidget = new QWidget(this);
    _centralWidget->setObjectName(QString::fromUtf8("_centralWidget"));
    _verticalLayout = new QVBoxLayout(_centralWidget);
    _verticalLayout->setObjectName(QString::fromUtf8("_verticalLayout"));
    _labelWidget = new QWidget(_centralWidget);
    _labelWidget->setObjectName(QString::fromUtf8("_labelWidget"));
    _verticalLayout_2 = new QVBoxLayout(_labelWidget);
    _verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
    _displayLabel = new QLabel(_labelWidget);
    _displayLabel->setObjectName(QString::fromUtf8("_displayLabel"));
    _displayLabel->setAlignment(Qt::AlignCenter);

    std::vector<float> data;
    setFrame();///TODO GIVE VECTOR TO FUNCTION;

    _buttonsWidget = new QWidget(_centralWidget);
    _buttonsWidget->setObjectName(QString::fromUtf8("_buttonsWidget"));
    _horizontalLayout = new QHBoxLayout(_buttonsWidget);
    _horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
    _connectButton = new QPushButton(_buttonsWidget);
    _connectButton->setObjectName(QString::fromUtf8("_connectButton"));
    _connectButton->setText(QString::fromUtf8("Connect"));

    _horizontalLayout->addWidget(_connectButton);

    _disconnectButton = new QPushButton(_buttonsWidget);
    _disconnectButton->setObjectName(QString::fromUtf8("_disconnectButton"));
    _disconnectButton->setText(QString::fromUtf8("Disconnect"));

    _horizontalLayout->addWidget(_disconnectButton);

    _saveResultButton = new QPushButton(_buttonsWidget);
    _saveResultButton->setObjectName(QString::fromUtf8("_saveResultButton"));
    _saveResultButton->setText(QString::fromUtf8("Save image"));

    _horizontalLayout->addWidget(_saveResultButton);

    _verticalLayout_2->addWidget(_displayLabel);
    _verticalLayout->addWidget(_labelWidget);

    _verticalLayout->addWidget(_buttonsWidget);

    _textLogWidget = new QWidget(_centralWidget);
    _textLogWidget->setObjectName(QString::fromUtf8("_textLogWidget"));
    _horizontalLayout_2 = new QHBoxLayout(_textLogWidget);
    _horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
    _messageLog = new QLabel(_textLogWidget);
    _messageLog->setObjectName(QString::fromUtf8("_messageLog"));

    _horizontalLayout_2->addWidget(_messageLog);

    _verticalLayout->addWidget(_textLogWidget);

    setCentralWidget(_centralWidget);

    updateLog("Program started");

    QMetaObject::connectSlotsByName(this);
}

void MainWindow::setFrame()
{

    cv::Mat img;
    //img = cv::imread("../Test.jpg");
    //cv::cvtColor(img, img,cv::COLOR_BGR2RGB);
  
    int width = 600;
    DataToMat dataverter(width);
    std::vector<float> data;
    for (size_t i = 0; i < 360; i++)
    {
        data.push_back((rand() % (width/2)) +5);
    }
   
    img = dataverter.convert(data);

    verticalLayout_2->addWidget(_displayLabel);
    verticalLayout->addWidget(_labelWidget);

    cv::cvtColor(img,img,cv::COLOR_BGR2RGB);

    QImage imag ((uchar*)img.data, img.cols, img.rows, img.step, QImage::Format_RGB888);

    _displayLabel->setPixmap(QPixmap::fromImage(imag));
}

void MainWindow::updateLog(const std::string& message)
{
    _messageLog->setText(QString::fromUtf8(message.c_str()));
}