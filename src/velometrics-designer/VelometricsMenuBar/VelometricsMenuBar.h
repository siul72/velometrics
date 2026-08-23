#pragma once

#include <QMenuBar>

class QAction;
class ActionManager;

class VelometricsMenuBar : public QMenuBar
{
    Q_OBJECT

public:

    explicit VelometricsMenuBar(ActionManager* actions,QWidget* parent = nullptr);

private:
    ActionManager* m_actions;

};
