
#include "MainToolBar.h"

#include <QAction>
#include <QIcon>
#include <QSize>

MainToolBar::MainToolBar(QWidget* parent)
    : QToolBar("Main Toolbar", parent)
{
    setObjectName("MainToolbar");

    setMovable(false);
    setFloatable(false);

    setIconSize(QSize(24, 24));

    createActions();
}

void MainToolBar::createActions()
{
    m_openAction = addAction(
        QIcon(":/icons/open.svg"),
        tr("Open"));

    m_saveAction = addAction(
        QIcon(":/icons/save.svg"),
        tr("Save"));

    addSeparator();

    m_importFitAction = addAction(
        QIcon(":/icons/import-fit.svg"),
        tr("Import FIT"));

    addSeparator();

    m_renderAction = addAction(
        QIcon(":/icons/render.svg"),
        tr("Render"));
}

QAction* MainToolBar::openAction() const
{
    return m_openAction;
}

QAction* MainToolBar::saveAction() const
{
    return m_saveAction;
}

QAction* MainToolBar::importFitAction() const
{
    return m_importFitAction;
}

QAction* MainToolBar::renderAction() const
{
    return m_renderAction;
}
