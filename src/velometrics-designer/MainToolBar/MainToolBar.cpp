
#include "MainToolBar.h"

#include <QAction>
#include <QIcon>
#include <QSize>
#include "../ActionManager/ActionManager.h"


MainToolBar::MainToolBar(ActionManager* action_manager, QWidget* parent) :
QToolBar("Main Toolbar", parent),  m_actionManager(action_manager)
{

    setObjectName("MainToolbar");
    setMovable(false);
    setFloatable(false);

    setIconSize(QSize(24, 24));

    setToolButtonStyle(
        Qt::ToolButtonIconOnly);

    addAction(
        m_actionManager->openProject());

    addAction(
        m_actionManager->saveProject());

    addSeparator();

    addAction(
        m_actionManager->loadTcx());

    addSeparator();

    addAction(
        m_actionManager->render());
}

