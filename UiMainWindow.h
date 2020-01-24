#ifndef DESIGNERIQFMCA_H
#define DESIGNERIQFMCA_H

#include "DataToMat.h"

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPlainTextEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include <QTimer>

QT_BEGIN_NAMESPACE

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

private:
    QWidget *centralwidget;
    QVBoxLayout *verticalLayout;
    QWidget *_labelWidget;
    QHBoxLayout *verticalLayout_2;
    QLabel *_displayLabel;
    QWidget *_buttonsWidget;
    QHBoxLayout *horizontalLayout;
    QPushButton *_connectButton;
    QPushButton *_disconnectButton;
    QPushButton *_saveResultButton;
    QWidget *_textLogWidget;
    QHBoxLayout *horizontalLayout_2;
    QPlainTextEdit *_textLogger;
    QMenuBar *menubar;
    QStatusBar *statusbar;
    DataToMat *_dataToMat;
    //id dataverter;

    QTimer _timer;

};

#endif // DESIGNERIQFMCA_H

