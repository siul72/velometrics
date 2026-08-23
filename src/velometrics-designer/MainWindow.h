#pragma once

#include <QMainWindow>

#include "ActionManager/ActionManager.h"

class QAction;
class QMenu;
class QTreeWidget;
class QDockWidget;
class QGraphicsView;
class QGraphicsScene;
class QTreeWidget;
class QLabel;
class MainToolBar;
class ElementsDock;
class PropertiesDock;
class CanvasWidget;
class VelometricsMenuBar;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget* parent = nullptr);

public slots:
    void onAboutTriggered();
    void onOpenProject();
    void onNewProject();
    void onSaveProject();
    void onSaveAsProject();
    void onNewTemplate();


private:
     void createStatusBar();

    // File
    QAction* m_newTemplateAction{};
    QAction* m_openTemplateAction{};
    QAction* m_saveTemplateAction{};
    QAction* m_saveAsTemplateAction{};
    QAction* m_exitAction{};

    // Activities
    QAction* m_loadFitAction{};
    QAction* m_loadGpxAction{};
    QAction* m_loadTcxAction{};
    QAction* m_loadSamsungAction{};

    // View
    QAction* m_zoomInAction{};
    QAction* m_zoomOutAction{};
    QAction* m_resetZoomAction{};
    QAction* m_showGridAction{};
    QAction* m_showGuidesAction{};
    QAction* m_showSafeAreaAction{};
    QAction* m_showRulersAction{};

    // Help
    QAction* m_aboutAction{};

    //Window composition
    ElementsDock* m_elementsDock;
    PropertiesDock* m_propertiesDock;
    CanvasWidget* m_canvas;
    VelometricsMenuBar* m_menuBar;
    QLabel* m_statusLabel{};
    MainToolBar* m_toolBar{};

    QString m_currentProjectFile;
    ActionManager* m_actionManager;
};

