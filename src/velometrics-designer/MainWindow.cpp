#include "MainWindow.h"

#include <QAction>
#include <qboxlayout.h>
#include <QMenuBar>
#include <QMessageBox>
#include <QToolBar>
#include <QGraphicsView>
#include  <QDockWidget>
#include <QTreeWidget>
#include <QTreeWidgetItem>
#include  <QLabel>
#include <QStatusBar>
#include  <QFileDialog>
#include <QSlider>

#include "Canvas/CanvasWidget.h"
#include "ElementsDock/ElementsDock.h"
#include "MainToolBar/MainToolBar.h"
#include "PropertiesDock/PropertiesDock.h"
#include "ActionManager/ActionManager.h"
#include "VelometricsMenuBar/VelometricsMenuBar.h"
#include "../velometrics-core/VelometricsCore.h"

MainWindow::MainWindow(QWidget* parent): QMainWindow(parent){

    m_actionManager = new ActionManager(this);
    m_menuBar = new VelometricsMenuBar(m_actionManager, this);
    setMenuBar(m_menuBar);
    m_toolBar = new MainToolBar(m_actionManager, this);
    addToolBar(Qt::TopToolBarArea,m_toolBar);

    auto* centralWidget = new QWidget(this);
    auto* layout = new QVBoxLayout(centralWidget);
    layout->setContentsMargins(0, 0, 0, 0);
    layout->setSpacing(0);

    m_canvas = new CanvasWidget(this);
    m_playbackWidget = new PlayToolBar(this);

    layout->addWidget(m_canvas, 1);
    layout->addWidget(m_playbackWidget, 0);

    setCentralWidget(centralWidget);

    m_elementsDock = new ElementsDock(this);
    addDockWidget( Qt::LeftDockWidgetArea, m_elementsDock);
    m_propertiesDock =  new PropertiesDock(this);
    addDockWidget( Qt::RightDockWidgetArea, m_propertiesDock);

    createStatusBar();

    setWindowTitle("Velometrics");
    resize(1600, 1000);

    connect(
    m_actionManager->about(),
    &QAction::triggered,
    this,
    &MainWindow::onAboutTriggered);

    connect(
    m_elementsDock,
    &ElementsDock::elementRequested,
    m_canvas,
    &CanvasWidget::addElement);

    const auto& core = VelometricsCore::instance();

    connect(&core,
        &VelometricsCore::activityLoaded,
        this,
        &MainWindow::onActivityLoaded);

    connect(&core,
        &VelometricsCore::activityLoaded,
        m_playbackWidget,
        &PlayToolBar::onActivityLoaded);

    connect(m_playbackWidget,
            &PlayToolBar::playRequested,
            &core,
            &VelometricsCore::play);

    connect(m_playbackWidget,
            &PlayToolBar::pauseRequested,
            &core,
            &VelometricsCore::pause);

    connect(m_playbackWidget,
            &PlayToolBar::stopRequested,
            &core,
            &VelometricsCore::stop);

    connect(m_playbackWidget,
            &PlayToolBar::seekRequested,
            &core,
            &VelometricsCore::seek);

    connect(&core,
            &VelometricsCore::playbackPositionChanged,
            m_playbackWidget,
            &PlayToolBar::setPosition);

    connect(&core,
            &VelometricsCore::timestampChanged,
            m_playbackWidget,
            &PlayToolBar::setTimestamp);

}


void MainWindow::onAboutTriggered(){
    QMessageBox::about(
        this,
        tr("About Velometrics"),
        tr(
            "Velometrics\n\n"
            "Telemetry Overlay Designer"));
}


void MainWindow::onOpenProject() {
    const QString fileName =
        QFileDialog::getOpenFileName(
            this,
            tr("Open Project"),
            QString(),
            tr("Velometrics Projects (*.vproj);;All Files (*)"));

    if (fileName.isEmpty())
    {
        return;
    }

    m_currentProjectFile = fileName;

    statusBar()->showMessage(
        tr("Opened project: %1").arg(fileName),
        5000);

    // TODO:
    // Load project from disk.
    // Deserialize widgets.
    // Restore timeline.
    // Refresh preview.
}

void MainWindow::onNewProject(){
}

void MainWindow::onSaveProject()
{
    QString fileName = m_currentProjectFile;

    if (fileName.isEmpty())
    {
        fileName =
            QFileDialog::getSaveFileName(
                this,
                tr("Save Project"),
                QString(),
                tr("Velometrics Projects (*.vproj)"));
    }

    if (fileName.isEmpty())
    {
        return;
    }

    m_currentProjectFile = fileName;

    statusBar()->showMessage(
        tr("Saved project: %1").arg(fileName),
        5000);

    // TODO:
    // Serialize project.
    // Save canvases.
    // Save widgets.
    // Save timeline.
}

void MainWindow::onSaveAsProject()
{
}

void MainWindow::onNewTemplate(){
}

void MainWindow::onActivityLoaded(const qsizetype numSamples) const {
    m_statusLabel->setText(
        QString("Loaded %1 samples").arg(numSamples));
}

void MainWindow::createStatusBar(){
    m_statusLabel = new QLabel("Ready");

    statusBar()->addWidget(m_statusLabel);

    statusBar()->addPermanentWidget(
        new QLabel("Canvas: 3840x2160"));

    statusBar()->addPermanentWidget(
        new QLabel("Zoom: 100%"));
}
