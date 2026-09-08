#include "ActionManager.h"
#include <QAction>
#include <QFileDialog>

ActionManager::ActionManager(QObject* parent) : QObject(parent)
{
    m_openProject = new QAction(tr("Open Project"), this);
    m_openProject->setIcon(QIcon(":/icons/open.svg"));
    m_saveProject = new QAction(tr("Save Project"), this);
    m_saveProject->setIcon( QIcon(":/icons/save.svg"));
    m_render = new QAction(tr("Render"), this);
    m_render->setIcon(QIcon(":/icons/render.svg"));
    m_newTemplate = new QAction("New Template", this);
    m_newTemplate->setShortcut(QKeySequence::New);
    m_openTemplate = new QAction("Open Template...", this);
    m_openTemplate->setShortcut(QKeySequence::Open);
    m_saveTemplate = new QAction("Save", this);
    m_saveTemplate->setShortcut(QKeySequence::Save);
    m_saveAsTemplate = new QAction("Save As...", this);
    m_loadFit = new QAction("Load FIT...", this);
    m_loadFit->setIcon(QIcon(":/icons/import-fit.svg"));
    m_loadGpx = new QAction("Load GPX...", this);
    m_loadTcx = new QAction("Load TCX...", this);
    m_loadSamsungHealth = new QAction(
            "Load Samsung Health Export...",
            this);
    m_zoomIn = new QAction("Zoom In", this);
    m_zoomOut = new QAction("Zoom Out", this);
    m_resetZoom = new QAction("Reset Zoom", this);
    m_showGrid = new QAction("Show Grid", this);
    m_showGrid->setCheckable(true);
    m_showGrid->setChecked(true);
    m_showGuides = new QAction("Show Guides", this);
    m_showGuides->setCheckable(true);
    m_showSafeArea = new QAction("Show Safe Area", this);
    m_showSafeArea->setCheckable(true);
    m_showRulers = new QAction("Show Rulers", this);
    m_showRulers->setCheckable(true);
    m_about = new QAction("About Velometrics", this);
    m_exit = new QAction("E&xit", this);
    m_exit->setShortcut(QKeySequence::Quit);

}

QAction* ActionManager::openProject() const
{
    return m_openProject;
}

QAction* ActionManager::saveProject() const
{
    return m_saveProject;
}

QAction* ActionManager::render() const
{
    return m_render;
}

QAction* ActionManager::newTemplate() const
{
    return m_newTemplate;
}

QAction* ActionManager::openTemplate() const
{
    return m_openTemplate;
}

QAction* ActionManager::saveTemplate() const
{
    return m_saveTemplate;
}

QAction* ActionManager::saveAsTemplate() const
{
    return m_saveAsTemplate;
}

QAction* ActionManager::loadFit() const
{
    return m_loadFit;
}

QAction* ActionManager::loadGpx() const
{
    return m_loadGpx;
}

QAction* ActionManager::loadTcx() const
{
    return m_loadTcx;
}

QAction* ActionManager::loadSamsungHealth() const
{
    return m_loadSamsungHealth;
}

QAction* ActionManager::zoomIn() const
{
    return m_zoomIn;
}

QAction* ActionManager::zoomOut() const
{
    return m_zoomOut;
}

QAction* ActionManager::resetZoom() const
{
    return m_resetZoom;
}

QAction* ActionManager::showGrid() const
{
    return m_showGrid;
}

QAction* ActionManager::showGuides() const
{
    return m_showGuides;
}

QAction* ActionManager::showSafeArea() const
{
    return m_showSafeArea;
}

QAction* ActionManager::showRulers() const
{
    return m_showRulers;
}

QAction* ActionManager::about() const
{
    return m_about;
}

QAction* ActionManager::exit() const
{
    return m_exit;
}

