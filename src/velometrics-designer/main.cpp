#include <QApplication>
#include "MainWindow.h"
#include "../velometrics-core/Metrics/Telemetry.h"

int main(int argc,char** argv){
    qRegisterMetaType<GeoPoint>();

    QApplication app(argc,argv);

    QApplication::setApplicationName("Velometrics");
    QApplication::setOrganizationName("Velometrics");
    QApplication::setApplicationVersion("0.1.0");

    MainWindow mainWindow;
    mainWindow.show();

    return QApplication::exec();
}