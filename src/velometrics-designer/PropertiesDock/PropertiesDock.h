#pragma once

#include <QDockWidget>

class QTreeWidget;
class QTreeWidgetItem;
class TelemetryWidgetItem;

class PropertiesDock : public QDockWidget
{
    Q_OBJECT

public:
    explicit PropertiesDock(QWidget* parent = nullptr);

    void clearProperties();
    void loadProperties(TelemetryWidgetItem* item);

    signals:
        void propertyChanged();

private slots:
    void onItemChanged(const QTreeWidgetItem* item, int column);

private:
    QTreeWidget* m_propertyTree{};
    TelemetryWidgetItem* m_currentItem{};
    bool m_updatingTree = false;
};

