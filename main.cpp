#include <QApplication>
#include "mainwindow.h"
#include "progressbarwindow.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    //ProgressBarWindow progressBar;
    MainWindow mainWindow;

    //QObject::connect(&progressBar, &ProgressBarWindow::progressComplete, [&]() {
        //progressBar.close();
        mainWindow.show();
    //});

    //progressBar.show();

    return a.exec();
}
