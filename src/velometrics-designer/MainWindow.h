#pragma once

#include <QMainWindow>

class QAction;
class QMenu;
class QTreeWidget;
class QDockWidget;
class QGraphicsView;
class QGraphicsScene;
class QTreeWidget;
class QLabel;
class MainToolBar;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget* parent = nullptr);

private slots:
    void onAboutTriggered();
private:
    void createMenus() const;
    void createActions();
    void createToolBar();
    void createCanvas();
    void createDocks();

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
    QTreeWidget* m_widgetTree{};
    QTreeWidget* m_propertyTree{};
    QGraphicsView* m_canvasView{};
    QGraphicsScene* m_canvasScene{};
    QLabel* m_statusLabel{};
    MainToolBar* m_toolBar{};

};

