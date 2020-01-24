#ifndef DESIGNERIQFMCA_H
#define DESIGNERIQFMCA_H

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

QT_BEGIN_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    MainWindow();
    ~MainWindow() override;
    void generateLayout();
    void retranslateUi(QMainWindow *MainWindow);

private:
    QWidget *centralwidget;
    QVBoxLayout *verticalLayout;
    QWidget *_labelWidget;
    QVBoxLayout *verticalLayout_2;
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

};

#endif // DESIGNERIQFMCA_H

