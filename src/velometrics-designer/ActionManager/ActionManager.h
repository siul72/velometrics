#pragma once

#include <QObject>

class QAction;

class ActionManager : public QObject
{
    Q_OBJECT

public:
    explicit ActionManager(QObject* parent = nullptr);

    [[nodiscard]] QAction* openProject() const;
    [[nodiscard]] QAction* saveProject() const;
    [[nodiscard]] QAction* render() const;

    [[nodiscard]] QAction* newTemplate() const;
    [[nodiscard]] QAction* openTemplate() const;
    [[nodiscard]] QAction* saveTemplate() const;
    [[nodiscard]] QAction* saveAsTemplate() const;

    [[nodiscard]] QAction* loadFit() const;
    [[nodiscard]] QAction* loadGpx() const;
    [[nodiscard]] QAction* loadTcx() const;
    [[nodiscard]] QAction* loadSamsungHealth() const;

    [[nodiscard]] QAction* zoomIn() const;
    [[nodiscard]] QAction* zoomOut() const;
    [[nodiscard]] QAction* resetZoom() const;

    [[nodiscard]] QAction* showGrid() const;
    [[nodiscard]] QAction* showGuides() const;
    [[nodiscard]] QAction* showSafeArea() const;
    [[nodiscard]] QAction* showRulers() const;

    [[nodiscard]] QAction* about() const;
    [[nodiscard]] QAction* exit() const;


private:
    QAction* m_newTemplate;
    QAction* m_openTemplate;
    QAction* m_saveTemplate;
    QAction* m_saveAsTemplate;

    QAction* m_loadFit;
    QAction* m_loadGpx;
    QAction* m_loadTcx;
    QAction* m_loadSamsungHealth;

    QAction* m_zoomIn;
    QAction* m_zoomOut;
    QAction* m_resetZoom;

    QAction* m_showGrid;
    QAction* m_showGuides;
    QAction* m_showSafeArea;
    QAction* m_showRulers;

    QAction* m_about;
    QAction* m_exit;
    QAction* m_openProject;
    QAction* m_saveProject;
    QAction* m_render;
};
