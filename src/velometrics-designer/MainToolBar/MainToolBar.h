#pragma once

#include <QToolBar>

class ActionManager;

class MainToolBar : public QToolBar
{
    Q_OBJECT

public:

    explicit MainToolBar(ActionManager* action_manager, QWidget* parent);


private slots:
    void loadTcx();

private:
    ActionManager* m_actionManager;

};
