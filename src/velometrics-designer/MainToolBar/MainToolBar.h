#pragma once

#include <QToolBar>

class QAction;

class MainToolBar : public QToolBar
{
    Q_OBJECT

public:
    explicit MainToolBar(QWidget* parent = nullptr);

    QAction* openAction() const;
    QAction* saveAction() const;
    QAction* importFitAction() const;
    QAction* renderAction() const;

private:
    void createActions();

    QAction* m_openAction {};
    QAction* m_saveAction {};
    QAction* m_importFitAction {};
    QAction* m_renderAction {};
};
