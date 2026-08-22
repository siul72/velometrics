#include <QApplication>
#include "MainWindow.h"

int main(int argc,char** argv){
    QApplication app(argc,argv);

    QApplication::setApplicationName("Velometrics");
    QApplication::setOrganizationName("Velometrics");
    QApplication::setApplicationVersion("0.1.0");

    MainWindow mainWindow;
    mainWindow.show();

    return app.exec();
}