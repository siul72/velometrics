
#include "VelometricsMenuBar.h"

#include <QAction>
#include <QKeySequence>

#include "../ActionManager/ActionManager.h"

VelometricsMenuBar::VelometricsMenuBar(ActionManager* actions, QWidget* parent):QMenuBar(parent)
                                                                                , m_actions(actions) {


    auto* fileMenu =  addMenu("&File");
    fileMenu->addAction(m_actions->newTemplate());
    fileMenu->addAction( m_actions->openTemplate());
    fileMenu->addSeparator();
    fileMenu->addAction( m_actions->saveTemplate());
    fileMenu->addAction( m_actions->saveAsTemplate());
    fileMenu->addSeparator();
    fileMenu->addAction(m_actions->exit());

    //
    // Templates
    //
    auto* templatesMenu = addMenu("&Templates");
    templatesMenu->addAction( "New 4K UHD");
    templatesMenu->addAction( "New 1080p HD");
    templatesMenu->addAction( "New 1440p QHD");
    templatesMenu->addSeparator();
    templatesMenu->addAction("Road Cycling");
    templatesMenu->addAction("Mountain Bike");
    templatesMenu->addAction( "Running");
    templatesMenu->addAction( "Triathlon");

    //
    // Activities
    //
    auto* activitiesMenu = addMenu("&Activities");
    activitiesMenu->addAction(m_actions->loadFit());
    activitiesMenu->addAction(m_actions->loadGpx());
    activitiesMenu->addAction(m_actions->loadTcx());
    activitiesMenu->addAction(m_actions->loadSamsungHealth());

    //
    // View
    //
    auto* viewMenu =  addMenu("&View");
    viewMenu->addAction(m_actions->zoomIn());
    viewMenu->addAction(m_actions->zoomOut());
    viewMenu->addAction(m_actions->resetZoom());
    viewMenu->addSeparator();

    viewMenu->addAction(m_actions->showGrid());
    viewMenu->addAction(m_actions->showGuides());
    viewMenu->addAction(m_actions->showSafeArea());
    viewMenu->addAction(m_actions->showRulers());

    //
    // Tools
    //

    auto* toolsMenu =  addMenu("&Tools");
    toolsMenu->addAction( "Align Left");
    toolsMenu->addAction( "Align Right");
    toolsMenu->addAction( "Align Top");
    toolsMenu->addAction( "Align Bottom");

    //
    // Help
    //

    auto* helpMenu = addMenu("&Help");
    helpMenu->addAction( "Documentation");
    helpMenu->addAction( "Keyboard Shortcuts");
    helpMenu->addSeparator();
    helpMenu->addAction(m_actions->about());
}
