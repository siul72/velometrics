#include "MainWindow.h"

#include <QAction>
#include <QMenuBar>
#include <QMessageBox>
#include <QToolBar>
#include <QGraphicsView>
#include  <QDockWidget>
#include <QTreeWidget>
#include <QTreeWidgetItem>
#include  <QLabel>
#include <QStatusBar>

#include "MainToolBar/MainToolBar.h"

MainWindow::MainWindow(QWidget* parent): QMainWindow(parent){
    createActions();
    createMenus();
    createToolBar();
    createCanvas();
    createDocks();
    createStatusBar();

    setWindowTitle("Velometrics");
    resize(1600, 1000);

}

void MainWindow::createMenus() const {
    //
    // File
    //
    QMenu* fileMenu = menuBar()->addMenu("&File");

    fileMenu->addAction(m_newTemplateAction);
    fileMenu->addAction(m_openTemplateAction);

    fileMenu->addSeparator();

    fileMenu->addAction(m_saveTemplateAction);
    fileMenu->addAction(m_saveAsTemplateAction);

    fileMenu->addSeparator();

    fileMenu->addAction(m_exitAction);

    //
    // Templates
    //
    QMenu* templatesMenu =
        menuBar()->addMenu("&Templates");

    templatesMenu->addAction("New 4K UHD");
    templatesMenu->addAction("New 1080p HD");
    templatesMenu->addAction("New 1440p QHD");

    templatesMenu->addSeparator();

    templatesMenu->addAction("Road Cycling");
    templatesMenu->addAction("Mountain Bike");
    templatesMenu->addAction("Running");
    templatesMenu->addAction("Triathlon");

    //
    // Activities
    //
    QMenu* activitiesMenu =
        menuBar()->addMenu("&Activities");

    activitiesMenu->addAction(m_loadFitAction);
    activitiesMenu->addAction(m_loadGpxAction);
    activitiesMenu->addAction(m_loadTcxAction);
    activitiesMenu->addAction(m_loadSamsungAction);

    //
    // View
    //
    QMenu* viewMenu =
        menuBar()->addMenu("&View");

    viewMenu->addAction(m_zoomInAction);
    viewMenu->addAction(m_zoomOutAction);
    viewMenu->addAction(m_resetZoomAction);

    viewMenu->addSeparator();

    viewMenu->addAction(m_showGridAction);
    viewMenu->addAction(m_showGuidesAction);
    viewMenu->addAction(m_showSafeAreaAction);
    viewMenu->addAction(m_showRulersAction);

    //
    // Tools
    //
    QMenu* toolsMenu =
        menuBar()->addMenu("&Tools");

    toolsMenu->addAction("Align Left");
    toolsMenu->addAction("Align Right");
    toolsMenu->addAction("Align Top");
    toolsMenu->addAction("Align Bottom");

    //
    // Help
    //
    QMenu* helpMenu =
        menuBar()->addMenu("&Help");

    helpMenu->addAction("Documentation");
    helpMenu->addAction("Keyboard Shortcuts");

    helpMenu->addSeparator();

    helpMenu->addAction(m_aboutAction);
}

void MainWindow::createActions()
{
    m_newTemplateAction = new QAction("&New Template", this);
    m_newTemplateAction->setShortcut(QKeySequence::New);

    m_openTemplateAction = new QAction("&Open Template...", this);
    m_openTemplateAction->setShortcut(QKeySequence::Open);

    m_saveTemplateAction = new QAction("&Save", this);
    m_saveTemplateAction->setShortcut(QKeySequence::Save);

    m_saveAsTemplateAction = new QAction("Save &As...", this);

    m_exitAction = new QAction("E&xit", this);
    m_exitAction->setShortcut(QKeySequence::Quit);

    m_loadFitAction = new QAction("Load FIT...", this);
    m_loadGpxAction = new QAction("Load GPX...", this);
    m_loadTcxAction = new QAction("Load TCX...", this);
    m_loadSamsungAction = new QAction(
        "Load Samsung Health Export...", this);

    m_zoomInAction = new QAction("Zoom In", this);
    m_zoomOutAction = new QAction("Zoom Out", this);
    m_resetZoomAction = new QAction("Reset Zoom", this);

    m_showGridAction = new QAction("Show Grid", this);
    m_showGridAction->setCheckable(true);
    m_showGridAction->setChecked(true);

    m_showGuidesAction = new QAction("Show Guides", this);
    m_showGuidesAction->setCheckable(true);

    m_showSafeAreaAction = new QAction("Show Safe Area", this);
    m_showSafeAreaAction->setCheckable(true);

    m_showRulersAction = new QAction("Show Rulers", this);
    m_showRulersAction->setCheckable(true);

    m_aboutAction = new QAction("About Velometrics", this);

    connect(
    m_aboutAction,
    &QAction::triggered,
    this,
    &MainWindow::onAboutTriggered);

}

void MainWindow::createToolBar()
{
    m_toolBar = new MainToolBar(this);

    addToolBar(Qt::TopToolBarArea, m_toolBar);

    connect(
        m_toolBar->openAction(),
        &QAction::triggered,
        this,
        &MainWindow::onOpenProject);

    connect(
        m_toolBar->saveAction(),
        &QAction::triggered,
        this,
        &MainWindow::onSaveProject);
}

void MainWindow::createCanvas(){
    m_canvasScene = new QGraphicsScene(this);

    m_canvasScene->setSceneRect(
        0,
        0,
        3840,
        2160);

    m_canvasScene->addRect(
        0,
        0,
        3840,
        2160);

    m_canvasView =
        new QGraphicsView(m_canvasScene);

    setCentralWidget(m_canvasView);
}

void MainWindow::createDocks()
{
    auto* widgetsDock =
        new QDockWidget("Widgets", this);

    m_widgetTree = new QTreeWidget();

    m_widgetTree->setHeaderHidden(true);

    auto* metrics =
        new QTreeWidgetItem({"Metrics"});

    metrics->addChild(
        new QTreeWidgetItem({"Speed"}));

    metrics->addChild(
        new QTreeWidgetItem({"Heart Rate"}));

    metrics->addChild(
        new QTreeWidgetItem({"Power"}));

    metrics->addChild(
        new QTreeWidgetItem({"Cadence"}));

    metrics->addChild(
        new QTreeWidgetItem({"Distance"}));

    metrics->addChild(
        new QTreeWidgetItem({"Elevation"}));

    auto* graphics =
        new QTreeWidgetItem({"Graphics"});

    graphics->addChild(
        new QTreeWidgetItem({"Text"}));

    graphics->addChild(
        new QTreeWidgetItem({"Image"}));

    graphics->addChild(
        new QTreeWidgetItem({"SVG"}));

    graphics->addChild(
        new QTreeWidgetItem({"Rectangle"}));

    m_widgetTree->addTopLevelItem(metrics);
    m_widgetTree->addTopLevelItem(graphics);

    widgetsDock->setWidget(m_widgetTree);

    addDockWidget(
        Qt::LeftDockWidgetArea,
        widgetsDock);
}

void MainWindow::onAboutTriggered(){
    QMessageBox::about(
        this,
        tr("About Velometrics"),
        tr(
            "Velometrics\n\n"
            "Telemetry Overlay Designer"));
}

void MainWindow::createStatusBar(){
    m_statusLabel = new QLabel("Ready");

    statusBar()->addWidget(m_statusLabel);

    statusBar()->addPermanentWidget(
        new QLabel("Canvas: 3840x2160"));

    statusBar()->addPermanentWidget(
        new QLabel("Zoom: 100%"));
}
