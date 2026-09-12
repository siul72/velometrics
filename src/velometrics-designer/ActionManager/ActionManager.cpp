#include "ActionManager.h"
#include <QAction>
#include <QFileDialog>

#include <QApplication>
#include <QStyle>

static QIcon themedIcon(const QString& themeName,
                        QStyle::StandardPixmap fallback)
{
    QIcon result = QIcon::fromTheme(themeName);

    if (result.isNull())
        result = QApplication::style()->standardIcon(fallback);

    return result;
}


ActionManager::ActionManager(QObject* parent)
    : QObject(parent)
{ 

    m_openProject = new QAction(
        themedIcon("document-open", QStyle::SP_DialogOpenButton),
        tr("Open Project"),
        this);

    m_saveProject = new QAction(
        themedIcon("document-save", QStyle::SP_DialogSaveButton),
        tr("Save Project"),
        this);

    m_render = new QAction(
        themedIcon("media-playback-start", QStyle::SP_MediaPlay),
        tr("Render"),
        this);

    m_newTemplate = new QAction(
        themedIcon("document-new", QStyle::SP_FileIcon),
        tr("New Template"),
        this);
    m_newTemplate->setShortcut(QKeySequence::New);

    m_openTemplate = new QAction(
        themedIcon("document-open", QStyle::SP_DialogOpenButton),
        tr("Open Template..."),
        this);
    m_openTemplate->setShortcut(QKeySequence::Open);

    m_saveTemplate = new QAction(
        themedIcon("document-save", QStyle::SP_DialogSaveButton),
        tr("Save"),
        this);
    m_saveTemplate->setShortcut(QKeySequence::Save);

    m_saveAsTemplate = new QAction(
        themedIcon("document-save-as", QStyle::SP_DialogSaveButton),
        tr("Save As..."),
        this);

    m_loadFit = new QAction(
        themedIcon("document-import", QStyle::SP_DriveHDIcon),
        tr("Load FIT..."),
        this);

    m_loadGpx = new QAction(
        themedIcon("document-import", QStyle::SP_DriveHDIcon),
        tr("Load GPX..."),
        this);

    m_loadTcx = new QAction(
        themedIcon("document-import", QStyle::SP_DriveCDIcon),
        tr("Load TCX..."),
        this);

    m_loadSamsungHealth = new QAction(
        themedIcon("document-import", QStyle::SP_DriveDVDIcon),
        tr("Load Samsung Health Export..."),
        this);

    m_zoomIn = new QAction(
        themedIcon("zoom-in", QStyle::SP_ArrowUp),
        tr("Zoom In"),
        this);

    m_zoomOut = new QAction(
        themedIcon("zoom-out", QStyle::SP_ArrowDown),
        tr("Zoom Out"),
        this);

    m_resetZoom = new QAction(
        themedIcon("zoom-original", QStyle::SP_BrowserReload),
        tr("Reset Zoom"),
        this);

    m_showGrid = new QAction(
        themedIcon("view-grid", QStyle::SP_FileDialogDetailedView),
        tr("Show Grid"),
        this);
    m_showGrid->setCheckable(true);
    m_showGrid->setChecked(true);

    m_showGuides = new QAction(
        themedIcon("view-list-details", QStyle::SP_FileDialogListView),
        tr("Show Guides"),
        this);
    m_showGuides->setCheckable(true);

    m_showSafeArea = new QAction(
        themedIcon("view-fullscreen", QStyle::SP_TitleBarMaxButton),
        tr("Show Safe Area"),
        this);
    m_showSafeArea->setCheckable(true);

    m_showRulers = new QAction(
        themedIcon("view-list-details", QStyle::SP_FileDialogDetailedView),
        tr("Show Rulers"),
        this);
    m_showRulers->setCheckable(true);

    m_about = new QAction(
        themedIcon("help-about", QStyle::SP_MessageBoxInformation),
        tr("About Velometrics"),
        this);

    m_exit = new QAction(
        themedIcon("application-exit", QStyle::SP_DialogCloseButton),
        tr("Exit"),
        this);
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

QAction* ActionManager::newTemplate() const {
    return m_newTemplate;
}

QAction* ActionManager::openTemplate() const {
    return m_openTemplate;
}

QAction* ActionManager::saveTemplate() const {
    return m_saveTemplate;
}

QAction* ActionManager::saveAsTemplate() const {
    return m_saveAsTemplate;
}

QAction* ActionManager::loadFit() const {
    return m_loadFit;
}

QAction* ActionManager::loadGpx() const {
    return m_loadGpx;
}

QAction* ActionManager::loadTcx() const {
    return m_loadTcx;
}

QAction* ActionManager::loadSamsungHealth() const {
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

