#pragma once

#include <QDockWidget>

class QListWidget;

class ElementsDock : public QDockWidget
{
    Q_OBJECT

public:
    explicit ElementsDock(QWidget* parent = nullptr);

    void addLayer(const QString& name) const;
    void removeLayer(const QString& name) const;

private:
    QListWidget* m_layerList;
};
