#include "UiMainWindow.h"
#include <iostream>
#include <utility>


//std::srand(time(NULL));


MainWindow::MainWindow() : _timer(this)
{
    generateLayout();

    QMetaObject::connectSlotsByName(this);
}

void MainWindow::generateLayout()
{
    if (objectName().isEmpty())
        setObjectName(QString::fromUtf8("MainWindow"));
        resize(505, 383);
    centralwidget = new QWidget(this);
    centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
    verticalLayout = new QVBoxLayout(centralwidget);
    verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
    _labelWidget = new QWidget(centralwidget);
    _labelWidget->setObjectName(QString::fromUtf8("_labelWidget"));
    verticalLayout_2 = new QHBoxLayout(_labelWidget);
    verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
    _displayLabel = new QLabel(_labelWidget);
    _displayLabel->setObjectName(QString::fromUtf8("_displayLabel"));
    _displayLabel->setAlignment(Qt::AlignCenter);


    setFrame();///TODO GIVE VECTOR TO FUNCTION;


    _buttonsWidget = new QWidget(centralwidget);
    _buttonsWidget->setObjectName(QString::fromUtf8("_buttonsWidget"));
    horizontalLayout = new QHBoxLayout(_buttonsWidget);
    horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
    _connectButton = new QPushButton(_buttonsWidget);
    _connectButton->setObjectName(QString::fromUtf8("_connectButton"));

    horizontalLayout->addWidget(_connectButton);

    _disconnectButton = new QPushButton(_buttonsWidget);
    _disconnectButton->setObjectName(QString::fromUtf8("_disconnectButton"));

    horizontalLayout->addWidget(_disconnectButton);

    _saveResultButton = new QPushButton(_buttonsWidget);
    _saveResultButton->setObjectName(QString::fromUtf8("_saveResultButton"));

    horizontalLayout->addWidget(_saveResultButton);


    verticalLayout->addWidget(_buttonsWidget);

    _textLogWidget = new QWidget(centralwidget);
    _textLogWidget->setObjectName(QString::fromUtf8("_textLogWidget"));
    horizontalLayout_2 = new QHBoxLayout(_textLogWidget);
    horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
    _textLogger = new QPlainTextEdit(_textLogWidget);
    _textLogger->setObjectName(QString::fromUtf8("_textLogger"));

    horizontalLayout_2->addWidget(_textLogger);


    verticalLayout->addWidget(_textLogWidget);

    setCentralWidget(centralwidget);
    menubar = new QMenuBar(this);
    menubar->setObjectName(QString::fromUtf8("menubar"));
    menubar->setEnabled(false);
    menubar->setGeometry(QRect(0, 0, 505, 22));
    setMenuBar(menubar);
    statusbar = new QStatusBar(this);
    statusbar->setObjectName(QString::fromUtf8("statusbar"));
    statusbar->setEnabled(false);
    setStatusBar(statusbar);

    retranslateUi(this);

    QMetaObject::connectSlotsByName(this);
}

void MainWindow::retranslateUi(QMainWindow *MainWindow)
{
    MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
    _connectButton->setText(QCoreApplication::translate("MainWindow", "PushButton", nullptr));
    _disconnectButton->setText(QCoreApplication::translate("MainWindow", "PushButton", nullptr));
    _saveResultButton->setText(QCoreApplication::translate("MainWindow", "PushButton", nullptr));
}

/*void MainWindow::setFrame()
{

}*/

void MainWindow::setFrame()
{

    cv::Mat img;
    //img = cv::imread("../Test.jpg");

    int width = 600;
    DataToMat dataverter(width);
    std::vector<float> data;
    for (size_t i = 0; i < 360; i++)
    {
        data.push_back((rand() % (width/2)) +5);
        //data.push_back(50);

    }
    //cv::imshow("test", dataverter.convert(data));
    //img = cv::imread(dataverter.convert(data));

    img = dataverter.convert(data);

    verticalLayout_2->addWidget(_displayLabel);
    verticalLayout->addWidget(_labelWidget);

    cv::cvtColor(img,img,cv::COLOR_BGR2RGB);

    QImage imag ((uchar*)img.data, img.cols, img.rows, img.step, QImage::Format_RGB888);

    _displayLabel->setPixmap(QPixmap::fromImage(imag));
    //_displayLabel->setScaledContents(true);
   // _displayLabel->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);
}

MainWindow::~MainWindow() {}

