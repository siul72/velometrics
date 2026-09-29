
#include "MainToolBar.h"

#include <QAction>
#include <QFileDialog>
#include <QIcon>
#include <QMessageBox>
#include <QSize>
#include "../ActionManager/ActionManager.h"
#include "../../velometrics-core/Activities/GpxLoader.h"
#include "../../velometrics-core/Activities/TCXLoader.h"
#include "../../velometrics-core/Metrics/TelemetryTrack.h"
#include "../../velometrics-core/VelometricsCore.h"

MainToolBar::MainToolBar(ActionManager* action_manager, QWidget* parent) :
QToolBar("Main Toolbar", parent),  m_actionManager(action_manager){
    setObjectName("MainToolbar");
    setMovable(false);
    setFloatable(false);
    setIconSize(QSize(24, 24));
    setToolButtonStyle(Qt::ToolButtonIconOnly);
    addAction(m_actionManager->loadTemplate());
    addAction(m_actionManager->saveTemplate());
    addSeparator();
    addAction(m_actionManager->loadGpx());
    addAction(m_actionManager->loadTcx());
    addSeparator();
    addAction(m_actionManager->render());
    connect(m_actionManager->loadGpx(), &QAction::triggered, this,  &MainToolBar::loadGpx);
    connect(m_actionManager->loadTcx(), &QAction::triggered, this,  &MainToolBar::loadTcx);
    connect(m_actionManager->render(),&QAction::triggered,&VelometricsCore::instance(),&VelometricsCore::render);
}

void MainToolBar::loadGpx(){
    const QString filePath = QFileDialog::getOpenFileName(
        this,
        tr("Open GPX File"),
        QString(),
        tr("GPX Files (*.gpx)")
    );

    if (filePath.isEmpty())
        return;

    if (!VelometricsCore::instance().loadActivity<GpxLoader>(filePath)){
        QMessageBox::warning(
            this,
            tr("Load Failed"),
            tr("Unable to load the selected GPX file.")
        );
        return;
    }

    // Process/display the track
    QDebug(QtDebugMsg) << "Loaded GPX track with " <<
        VelometricsCore::instance().getTelemetryTrack().samples.count() << " samples.";
}

void MainToolBar::loadTcx(){
    const QString filePath = QFileDialog::getOpenFileName(
        this,
        tr("Open TCX File"),
        QString(),
        tr("TCX Files (*.tcx)")
    );

    if (filePath.isEmpty())
        return;

    if (!VelometricsCore::instance().loadActivity<TcxLoader>(filePath)){
        QMessageBox::warning(
            this,
            tr("Load Failed"),
            tr("Unable to load the selected TCX file.")
        );
        return;
    }

    // Process/display the track
    QDebug(QtDebugMsg) << "Loaded TCX track with " <<
        VelometricsCore::instance().getTelemetryTrack().samples.count() << " samples.";
}


